//
//  MLevel.cpp
//  MonteCarlo
//
//  Created by Adrien Bruchet on 29/04/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

#include "MLevel.h"

using namespace std;


MLevel::MLevel(){
    
}

MLevel::MLevel(double strike, std::vector<int> k, std::vector<int> n, std::vector<SetOfPaths>  underlyings):k_L(k), n_L(n){
    
    for (int l = 0; l < underlyings.size(); l++) {
        underlying_traj.push_back(make_shared<SetOfPaths>(underlyings[l]));
        Z_traj.push_back(make_shared<SetOfPaths>(underlyings[l].massExtractPut(strike)));
    }
    vector<double> EuroPoints;
    for (int k = 0; k < 50; k++) {
        double P_t = callput(underlying_traj[0]->getPath(0)->getPoint(0), strike,k*0.5/50, 0.06, 0, 0.4, -1);
        EuroPoints.push_back(P_t);
    }
    euro_traj = Path(EuroPoints);
    K = strike;
}

MLevel::~MLevel(){
    
}

double MLevel::first_step(){
    cout << "l = 0" << endl;
    shared_ptr<MCEstimator> Estim = make_shared<MCEstimator>();
    for (int n = 0; n< n_L[0]; n++) {
        cout << "n = " << n << endl;
        Path sj = *(underlying_traj[0]->getPath(n));
        Path Z_M = *(Z_traj[0]->getPath(n)) - compute_M_k(sj, euro_traj, k_L[0], K, 0.4, 0.06);
        Estim->addPath(Z_M);
    }
    double Y_0 = Estim->computeMeanSup();
    return Y_0;
}

double MLevel::next_steps(){
    double Y_next = 0;
    shared_ptr<MCEstimator> Estim;
    for (int l = 1; l < k_L.size(); l++) {
        cout << "l = " << l << endl;
        vector<double> max_l;
        for (int n = 0; n < n_L[l]; n++) {
            Path sj = *(underlying_traj[0]->getPath(n));
            Path Z_M_l = *(Z_traj[l]->getPath(n)) - compute_M_k(sj, euro_traj, k_L[l], K, 0.4, 0.06);
            Path Z_M_l_1 = *(Z_traj[l]->getPath(n)) - compute_M_k(sj, euro_traj, k_L[l-1], K, 0.4, 0.06);
            max_l.push_back(Z_M_l.getMax() - Z_M_l_1.getMax());
        }
        Y_next = Y_next + Estim->computeMean(max_l);
    }
    return Y_next;
}