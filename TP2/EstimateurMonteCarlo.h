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
#include <vector>

//classe qui servira a toutes les estimations MC
class MCEstimator{
    
public:
    MCEstimator();
    MCEstimator(std::shared_ptr<SetOfPaths> SOPaths);
    ~MCEstimator();
    
    void setPaths(std::shared_ptr<SetOfPaths> const& newSetPaths);
    std::shared_ptr<SetOfPaths> & getPaths();
    
    double computeMeanSup();
        
private:
    std::shared_ptr<SetOfPaths> MCPaths;
    
};

//minimisation en lambda
double minLambda(SetOfPaths const& Z, SetOfPaths const& martingales);

#endif /* defined(__MonteCarlo__EstimateurMonteCarlo__) */
