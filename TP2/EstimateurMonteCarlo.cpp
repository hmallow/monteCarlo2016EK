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

MCEstimator::MCEstimator(shared_ptr<SetOfPaths> SOPaths){
    
    MCPaths = SOPaths;
}

MCEstimator::~MCEstimator(){
    
}

void MCEstimator::setPaths(shared_ptr<SetOfPaths> const& newSetPaths){
    MCPaths = newSetPaths;
}

std::shared_ptr<SetOfPaths> & MCEstimator::getPaths(){
    return MCPaths;
}


//calcule l'esperance empirique
double MCEstimator::computeMeanSup(){
    double mean = 0;
    vector<double> sups = MCPaths->computeSups();
    int N = sups.size();
    for (int i = 0; i < N; i++) {
        mean += sups[i];
    }
    mean = double(mean/N);
    return mean;
}

vector<double> minLambda(SetOfPaths const& Z, SetOfPaths const& martingales){
    
    //initialisation
    double epsilon = 1e-9;
    double l_min = 0;
    double l_max = 1e9;
    double min = l_min;
    double max = l_max;
    double max_it = 1e3;
    int it = 0;
    MCEstimator estim = MCEstimator();
    
    //boucle de dichotomie
    while (it < max_it && (max-min) > epsilon) {
        double mil = (max - min)*0.5;
        
        //calcul valeur centrale
        shared_ptr<SetOfPaths> M_ptr = make_shared<SetOfPaths>(Z-martingales*mil);
        estim.setPaths(M_ptr);
        double val_m = estim.computeMeanSup();
        
        //calcul f(min)
        M_ptr = make_shared<SetOfPaths>(Z-martingales*min);
        estim.setPaths(M_ptr);
        double val_inf = estim.computeMeanSup();
        
        //calcul f(max)
        M_ptr = make_shared<SetOfPaths>(Z-martingales*max);
        estim.setPaths(M_ptr);
        double val_sup = estim.computeMeanSup();
        
        //comparaison
        if (val_inf*val_m > 0) {
            min = mil;
        }
        else{
            max = mil;
        }
        
    }
    vector<double> a;
    
    return a;
}



