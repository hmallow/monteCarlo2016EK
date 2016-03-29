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
#include "Trajectoires.h"
#include <vector>

//classe qui servira a toutes les estimations MC
class MCEstimator{
    
public:
    MCEstimator();
    MCEstimator(std::vector<std::shared_ptr<Path>> paths);
    ~MCEstimator();
    
    std::vector<std::shared_ptr<Path>> & setPaths();
    std::vector<std::shared_ptr<Path>> const getPaths();
    
    void const addPath(Path & path);
    
    double computeMean();
    
private:
    std::vector<std::shared_ptr<Path>> MCPaths;
    
};

#endif /* defined(__MonteCarlo__EstimateurMonteCarlo__) */
