//
//  EstimateurMonteCarlo.cpp
//  MonteCarlo
//
//  Created by Adrien Bruchet on 29/03/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

#include "EstimateurMonteCarlo.h"

using namespace std;


MCEstimator::MCEstimator(){
    
}

MCEstimator::MCEstimator(std::vector<std::shared_ptr<Path>> paths, std::vector<std::shared_ptr<Path>> martingales){
    
    MCPaths = paths;
}

MCEstimator::~MCEstimator(){
    
}

//calcule l'esperance empirique
double MCEstimator::computeMean(){
    double mean = 0;
    vector<double> sups = MCPaths.computeSups();
    int N = sups.size();
    for (int i = 0; i < N; i++) {
        mean += sups[i];
    }
    mean = double(mean/N);
    return mean;
}