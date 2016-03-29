//
//  EstimateurMonteCarlo.cpp
//  MonteCarlo
//
//  Created by Adrien Bruchet on 29/03/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

#include "EstimateurMonteCarlo.h"

using namespace std;



void const MCEstimator::addPath(Path & path){
    
    shared_ptr<Path> path_ptr = make_shared<Path>(path);
    MCPaths.push_back(path_ptr);
}