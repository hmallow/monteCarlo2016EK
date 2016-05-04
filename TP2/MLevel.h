//
//  MLevel.h
//  MonteCarlo
//
//  Created by Adrien Bruchet on 29/04/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

#ifndef __MonteCarlo__MLevel__
#define __MonteCarlo__MLevel__

#include <stdio.h>
#include "EstimateurMonteCarlo.h"
#include <vector>


class MLevel{
    
public:
    MLevel();
    MLevel(double strike, double T, int Nt,std::vector<int> k, std::vector<int> n, std::vector<SetOfPaths> underlyings);
    ~MLevel();
    
    
    double first_step();
    double next_steps();
    
private:
    std::vector<std::shared_ptr<SetOfPaths>> underlying_traj;
    std::vector<std::shared_ptr<SetOfPaths>> Z_traj;
    Path euro_traj;
    double K;
    std::vector<int> k_L;
    std::vector<int> n_L;
    double time_step;
    double maturity;
    double interest_rate;
    double vol;
    
};

#endif /* defined(__MonteCarlo__MLevel__) */
