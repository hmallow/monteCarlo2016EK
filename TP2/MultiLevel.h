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
    MultiLevel(int L, int k, int n, std::shared_ptr<SetOfPaths> underlyings);
    ~MultiLevel();
    
    std::vector<vector<double>> computeTaus(Path const& EuropeanOption);
    
    Path computeM_k(Path const& underlying,vector<double> const& tau_i, int k_l);
    
    double step_n_0();
    
    
    
    
private:
    double T = 0.5;
    double r=0.06;
    double vol=0.4;
    int NbLevels;
    std::vector<int> k_L;
    std::vector<int> n_L;
    int Nb_Total;
    std::shared_ptr<SetOfPaths> sj_trajectories;
    std::shared_ptr<SetOfPaths> Z_trajectories;
    std::shared_ptr<SetOfPaths> M_trajectories;
    std::vector<vector<double>> taus;
    std::shared_ptr<MCEstimator> MCEstimator;
    
};

#endif /* defined(__MonteCarlo__MultiLevel__) */