//
//  MultiLevel.cpp
//  MonteCarlo
//
//  Created by Adrien Bruchet on 24/04/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

using namespace std;

#include "MultiLevel.h"


MultiLevel::MultiLevel(){
    
}

MultiLevel::MultiLevel(int L, std::vector<int> k, std::vector<int> n, std::vector<std::shared_ptr<SetOfPaths>> underlyings){
    
    NbLevels = L;
    n_L = n;
    k_L = k;
    sj_trajectories = underlyings;
    taus = vector<vector<vector<double>>>();
}

MultiLevel::~MultiLevel(){
    
}

void MultiLevel::computeTaus(Path const& EuropeanOption){
    
    int J = sj_trajectories[0]->getPath(0)->Points().size();
    for (int l = 0; l < NbLevels; l++) {
        vector<vector<double>> tau_l;
        for (int n = 0; n< n_L[l]; n++) {
            vector<double> tau_n;
            for (int i = 0; i < J; i++) {
                bool found = false;
                int j = i;
                while (found == false||j != J) {
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
    new_points.push_back(0);
    double sum = 0;
    
    for (int j = 1; j < J ; j++) {
        shared_ptr<SetOfPaths> sub_set_j;
        shared_ptr<SetOfPaths> sub_set_j_1;
        for (int k = 0; k < k_l; k++) {
            vector<double> points = Sim_S(J, tau_i[j], vol, underlying.Points()[j], r, T);
            vector<double> points_1 = Sim_S(J, tau_i[j] + 1, vol, underlying.Points()[j-1], r, T);
            Path sub_path_j = Path(points);
            sub_set_j->addPath(sub_path_j);
            Path sub_path_j_1 = Path(points_1);
            sub_set_j_1->addPath(sub_path_j_1);
        }
        MCEstimator->setPaths(sub_set_j);
        double expect_j = MCEstimator->computeMean();
        MCEstimator->setPaths(sub_set_j_1);
        double expect_j_1 = MCEstimator->computeMean();
        double delta_i = expect_j - expect_j_1;
        sum+= delta_i;
        new_points.push_back(sum);
    }
    Path M_k = Path(new_points);
    return M_k;
    
}

double MultiLevel::step_n_0(){
    
    shared_ptr<SetOfPaths> SOPath;
    for (int i = 0; i < n_L[0]; i++) {
        Path diff_traj = *(Z_trajectories[0])->getPath(i) + computeM_k(*(sj_trajectories[0]->getPath(i)), taus[0][i], k_L[0])*(-1);
        SOPath->addPath(diff_traj);
    }
    MCEstimator->setPaths(SOPath);
    double Y_0 = MCEstimator->computeMeanSup();
    return Y_0;
}

double MultiLevel::next_steps(){
    
    double sum_levels = 0;
    for (int l = 1; l < NbLevels + 1; l++) {
        shared_ptr<SetOfPaths> set_k_l;
        shared_ptr<SetOfPaths> set_k_l_1;
        for (int i = 0; i < n_L[l]; i++) {
            Path Mk_l = computeM_k(*(sj_trajectories[l]->getPath(i)), taus[l][i], k_L[l]);
            Path Mk_l_1 = computeM_k(*(sj_trajectories[l]->getPath(i)), taus[l][i], k_L[l-1]);
            Path diff_path = *((Z_trajectories[l])->getPath(i)) + Mk_l*(-1);
            Path diff_path_1 = *((Z_trajectories[l])->getPath(i)) + Mk_l_1*(-1);
            set_k_l->addPath(diff_path);
            set_k_l_1->addPath(diff_path_1);
        }
        MCEstimator->setPaths(set_k_l);
        double sup_l = MCEstimator->computeMeanSup();
        MCEstimator->setPaths(set_k_l_1);
        double sup_l_1 = MCEstimator->computeMeanSup();
        sum_levels += sup_l - sup_l_1;
    }
    
    return sum_levels + step_n_0();
}

