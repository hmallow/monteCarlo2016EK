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

MultiLevel::MultiLevel(int L, int k, int n, shared_ptr<SetOfPaths> underlyings){
    
}

MultiLevel::~MultiLevel(){
    
}

vector<vector<double>> MultiLevel::computeTaus(Path const& EuropeanOption){
    
    int J = sj_trajectories->getPath(0)->Points().size();
    vector<vector<double>> taus;
    for (int n = 0; n< Nb_Total; n++) {
        vector<double> tau_n;
        for (int i = 0; i < J; i++) {
            bool found = false;
            int j = i;
            while (found == false||j != J) {
                if (EuropeanOption.Points()[j] <= Z_trajectories->getPath(n)->Points()[j]) {
                    found = true;
                    tau_n.push_back(j);
                }
                j++;
            }
        }
    }
    
    return taus;
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
        Path diff_traj = *(Z_trajectories)->getPath(i) + computeM_k(*(sj_trajectories->getPath(i)), taus[i], k_L[0])*(-1);
    }
    
    return 2;
}


