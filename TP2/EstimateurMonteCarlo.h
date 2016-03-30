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
    MCEstimator(std::vector<std::shared_ptr<Path>> paths, std::vector<std::shared_ptr<Path>> martingales);
    ~MCEstimator();
    
    std::vector<std::shared_ptr<Path>> & setPaths();
    std::vector<std::shared_ptr<Path>> const getPaths();
    
    double computeMean();
    
    double Lambda() const;
    double & Lambda();
        
private:
    SetOfPaths MCPaths;
    double lambda;
    SetOfPaths MartingalePaths;
    
    
};

#endif /* defined(__MonteCarlo__EstimateurMonteCarlo__) */
