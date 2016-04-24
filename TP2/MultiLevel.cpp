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

Path MultiLevel::computeM_k(Path const& underlying,vector<double> const& tau_i){
    
    vector<double> new_points;
    Path M_k = Path(new_points);
    return M_k;
    
}

double MultiLevel::step_n_0(){
    
    for (int i = 0; i < n_L[0]; i++) {
        
    }
    
    return 2;
}


