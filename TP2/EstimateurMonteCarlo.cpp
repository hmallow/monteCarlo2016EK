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
    MartingalePaths = martingales;
}

MCEstimator::~MCEstimator(){
    
}



void const MCEstimator::addPath(Path & path){
    
    shared_ptr<Path> path_ptr = make_shared<Path>(path);
    MCPaths.push_back(path_ptr);
}

double & MCEstimator::Lambda(){
    
    return lambda;
}

double MCEstimator::Lambda() const {
    
    return lambda;
}

double MCEstimator::findMinLambda(){
    
    double lambda = 0;
    
    return lambda;
}
