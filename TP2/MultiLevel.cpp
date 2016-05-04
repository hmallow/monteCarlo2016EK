//
//  MultiLevel.cpp
//  MonteCarlo
//
//  Created by Adrien Bruchet on 24/04/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

using namespace std;

#include "MultiLevel.h"
#include "vector.h"


MultiLevel::MultiLevel(){
    
}

MultiLevel::MultiLevel(int L, std::vector<int> k, std::vector<int> n, std::vector<std::shared_ptr<SetOfPaths>> underlyings){
    
    NbLevels = L;
    n_L = n;
    k_L = k;
    sj_trajectories = underlyings;
    for (int i = 0; i < underlyings.size(); i++) {
        SetOfPaths Z_l =  SetOfPaths(*(underlyings[i]));
        Z_l.massConvertToPut(strike);
        Z_trajectories.push_back(make_shared<SetOfPaths>(Z_l));
    }
    //Z_trajectories = underlyings;
    taus = vector<vector<vector<double>>>();
}

MultiLevel::~MultiLevel(){
    
}

void MultiLevel::computeTaus(Path const& EuropeanOption){
    
    int J = sj_trajectories[0]->getPath(0)->Points().size();
    for (int l = 0; l < NbLevels+1; l++) {
        vector<vector<double>> tau_l;
        for (int n = 0; n< n_L[l]; n++) {
            vector<double> tau_n;
            for (int i = 0; i < J; i++) {
                bool found = false;
                int j = i;
                while (found == false && j != J) {
                    if (EuropeanOption.Points()[j] <= Z_trajectories[l]->getPath(n)->Points()[j]) {
                        found = true;
                        tau_n.push_back(j);
                    }
                    j++;
                }
            }
            tau_l.push_back(tau_n);
        }
        taus.push_back(tau_l);
    }
}

Path MultiLevel::computeM_k(Path const& underlying,vector<double> const& tau_i, int k_l){
    
    int J = underlying.Points().size();
    
    vector<double> new_points;
    new_points.push_back(0); //M_k nulle en 0
    double sum = 0;
    
    //boucle sur les instants
    for (int j = 1; j < J ; j++) {
        
        clock_t begin_j = clock();
        //deux ensembles de trajectoires pour les deux esperances
        //conditionnelles
        vector<shared_ptr<Path>> dumm_set;
        shared_ptr<SetOfPaths> sub_set_j = make_shared<SetOfPaths>(dumm_set);
        shared_ptr<SetOfPaths> sub_set_j_1 = make_shared<SetOfPaths>(dumm_set);
        
        //boucle sur le nb de sous-simulations
        for (int k = 0; k < k_l; k++) {
            //simulation de deux trajectoires jusqu'en tau_j
            int horizon = tau_i[j] - j;
            int horizon_1 = tau_i[j] -(j-1);
            vector<double> points = Sim_S(J, horizon, vol, underlying.Points()[j], r, T);
            vector<double> points_1 = Sim_S(J, horizon_1, vol, underlying.Points()[j-1], r, T);
            Path sub_path_j = Path(points);
            sub_set_j->addPath(sub_path_j);
            Path sub_path_j_1 = Path(points_1);
            sub_set_j_1->addPath(sub_path_j_1);
            
        }
        
        //calcul d'un estimateur de E(Z_tau_i|Fi) et E(Z_tau_i|Fi-1)
        Estimator->setPaths(sub_set_j);
        double expect_j = Estimator->computeMean();
        Estimator->setPaths(sub_set_j_1);
        double expect_j_1 = Estimator->computeMean();
        double delta_i = expect_j - expect_j_1;
        sum+= delta_i;
        new_points.push_back(sum);
        clock_t end_j = clock();
        double elapsed_secs_j = double(end_j - begin_j) / CLOCKS_PER_SEC;
        cout << "pour j = " << j << " , " << elapsed_secs_j << " secondes" << endl;
    }
    
    Path M_k = Path(new_points);
    return M_k;
    
}

double MultiLevel::step_n_0(){
    
    vector<shared_ptr<Path>> dumm_set;
    shared_ptr<SetOfPaths> SOPath = make_shared<SetOfPaths>(dumm_set);
    for (int i = 0; i < n_L[0]; i++) {
        Path diff_traj = *(Z_trajectories[0])->getPath(i) + computeM_k(*(sj_trajectories[0]->getPath(i)), taus[0][i], k_L[0])*(-1);
        SOPath->addPath(diff_traj);
    }
    Estimator->setPaths(SOPath);
    double Y_0 = Estimator->computeMeanSup();
    return Y_0;
}

double MultiLevel::next_steps(){
    
    double sum_levels = 0;
    for (int l = 1; l < NbLevels + 1; l++) {
        cout << "level " << l << endl;
        vector<shared_ptr<Path>> dumm_set;
        shared_ptr<SetOfPaths> set_k_l = make_shared<SetOfPaths>(dumm_set);
        shared_ptr<SetOfPaths> set_k_l_1 = make_shared<SetOfPaths>(dumm_set);
        for (int i = 0; i < n_L[l]; i++) {
            Path Mk_l = computeM_k(*(sj_trajectories[l]->getPath(i)), taus[l][i], k_L[l]); //bad access l=3 ici
            Path Mk_l_1 = computeM_k(*(sj_trajectories[l]->getPath(i)), taus[l][i], k_L[l-1]);
            Path diff_path = *((Z_trajectories[l])->getPath(i)) + Mk_l*(-1);
            Path diff_path_1 = *((Z_trajectories[l])->getPath(i)) + Mk_l_1*(-1);
            set_k_l->addPath(diff_path);
            set_k_l_1->addPath(diff_path_1);
        }
        Estimator->setPaths(set_k_l);
        double sup_l = Estimator->computeMeanSup();
        Estimator->setPaths(set_k_l_1);
        double sup_l_1 = Estimator->computeMeanSup();
        sum_levels += sup_l - sup_l_1;
    }
    
    return sum_levels + step_n_0();
}

double getSup(vector<double> vect){
    double max = vect[0];
    for(double elem:vect){
        if (elem > max){
            max = elem;
        }
    }
    return max;
}

double getMean(vector<double> vect){
    double sum = 0;
    for (int k = 0; k < vect.size(); k++) {
        sum+=vect[k];
    }
    int N = vect.size();
    return sum/(double(N));
}

double test_broadie(){
    
    int N = 150;
    double T = 0.5;
    double r=0.06;
    double vol=0.4;
    int Nt = 50;
    
    double spot = 80;
    double K = 100;
    vector<vector<double>> sample_paths;
    vector<vector<double>> Z_paths;
    //creation des trajectoires
    for (int n = 0; n < N; n++) {
        cout << "n vaut " << n << endl;
        vector<double> res = Sim_S_M(Nt, vol, spot, r, K, T)[0];
        sample_paths.push_back(res);
        vector<double> z_traj;
        for (int k = 0; k < res.size(); k++) {
            if (K - res[k] > 0) {
                z_traj.push_back(K-res[k]);
            }
            else{
                z_traj.push_back(0);
            }
        }
        Z_paths.push_back(z_traj);
    }
    
    //calcul des taus
    vector<vector<double>> taus;
    for (int n = 0; n < N; n++) {
        cout << "n vaut " << n << endl;
        vector<double> tau_n;
        for (int j = 0; j < Nt+1; j++) {
            int k = j;
            bool found = false;
            while (found == false && k < Nt) {
                vector<double> eurotraj;
                for (int p = k; p < Nt+1; p++) {
                    eurotraj.push_back(callput(sample_paths[n][p], K, (Nt-p)*T/Nt, r, 0, vol, -1)*exp(-r*(Nt-p)*T/Nt));
                }
                if (getSup(eurotraj) >= Z_paths[n][k]) {
                    found = true;
                    tau_n.push_back(k);
                }
                else{
                    k++;
                }
            }
            if (k == Nt && found == false) {
                tau_n.push_back(k);
            }
        }
        taus.push_back(tau_n);
    }
    
    
    //calcul de la martingale M_k
    int NbSim = 50;
    vector<vector<double>> mart_paths;
    vector<double> mart_end;
    for (int n = 0; n < N; n++) {
        cout << "n vaut " << n << endl;
        vector<double> M_points;
        M_points.push_back(0);
        for (int j = 1; j < Nt+1; j++) {
            vector<double> inner_traj;
            vector<double> inner_traj_1;
            for (int k = 0; k< NbSim; k++) {
                double inner_sim = Sim_S_M(Nt, vol, sample_paths[n][j], r, K, T)[0][taus[n][j]-j];
                double inner_point = 0;
                if (K - inner_sim > 0) {
                    inner_point = (K - inner_sim)*exp(-r*taus[n][j]-j)*(T/(Nt-1));
                }
                inner_traj.push_back(inner_point);
                double inner_sim_1 = Sim_S_M(Nt, vol, sample_paths[n][j-1], r, K, T)[0][taus[n][j]-j];
                double inner_point_1 = 0;
                if (K - inner_sim_1 > 0) {
                    inner_point_1 = (K - inner_sim_1)*exp(-r*taus[n][j]-(j-1))*(T/(Nt-1));
                }
                inner_traj_1.push_back(inner_point_1);
            }
            double esp_fi = getMean(inner_traj);
            double esp_fi_1 = getMean(inner_traj_1);
            double delta_i = esp_fi - esp_fi_1;
            double sum = M_points.back();
            M_points.push_back(delta_i + sum);
        }
        mart_paths.push_back(M_points);
        mart_end.push_back(M_points.back());
    }
    
    double test = getMean(mart_end);
    vector<double> sups;
    for (int n = 0; n < N; n++) {
        vector<double> Z_M_i = Z_paths[n] - mart_paths[n];
        double sup = getSup(Z_M_i);
        sups.push_back(sup);
    }
    double Y_0 = getMean(sups);
    return Y_0;
}

