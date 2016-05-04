//
//  EstimateurMonteCarlo.h
//  MonteCarlo
//
//  Created by Adrien Bruchet on 29/03/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

#ifndef __MonteCarlo__EstimateurMonteCarlo__
#define __MonteCarlo__EstimateurMonteCarlo__

#include <stdio.h>
#include "SetOfPaths.h"
#include "MonteCarlo_Put.h"
#include <vector>

//classe qui servira a toutes les estimations MC
class MCEstimator{
    
public:
    MCEstimator();
    MCEstimator(std::shared_ptr<SetOfPaths> SOPaths);
    ~MCEstimator();
    
    void setPaths(std::shared_ptr<SetOfPaths> const& newSetPaths);
    std::shared_ptr<SetOfPaths> & getPaths();
    void addPath(Path & path);
    
    double computeMeanSup();
    double computeMean();
    
    double computeMean(vector<double> const& points);
        
private:
    std::shared_ptr<SetOfPaths> MCPaths;
    
};

//minimisation en lambda
double minLambda(SetOfPaths const& Z, SetOfPaths const& martingales);

Path compute_M_k(Path const& traj,int nbSim, double strike, double T, double r);


#endif /* defined(__MonteCarlo__EstimateurMonteCarlo__) */
