//
//  MultiLevel.h
//  MonteCarlo
//
//  Created by Adrien Bruchet on 24/04/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

#ifndef __MonteCarlo__MultiLevel__
#define __MonteCarlo__MultiLevel__

#include <stdio.h>
#include <vector>
#include "EstimateurMonteCarlo.h"
#include "MonteCarlo_Geo.h"
#include "MonteCarlo_Put.h"


class MultiLevel{
    
public:
    MultiLevel();
    MultiLevel(int L, std::vector<int> k, std::vector<int> n, std::vector<std::shared_ptr<SetOfPaths>>  underlyings);
    ~MultiLevel();
    
    void computeTaus(Path const& EuropeanOption);
    
    Path computeM_k(Path const& underlying,vector<double> const& tau_i, int k_l);
    
    double step_n_0();
    double next_steps();

    
private:
    double T = 0.5;
    double r=0.06;
    double vol=0.4;
    int NbLevels;
    std::vector<int> k_L;
    std::vector<int> n_L;
    int Nb_Total;
    std::vector<std::shared_ptr<SetOfPaths>> sj_trajectories;
    std::vector<std::shared_ptr<SetOfPaths>> Z_trajectories;
    std::vector<vector<vector<double>>> taus;
    std::shared_ptr<MCEstimator> Estimator = std::make_shared<MCEstimator>();
    
};

#endif /* defined(__MonteCarlo__MultiLevel__) */