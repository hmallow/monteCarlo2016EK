//
//  EstimateurMonteCarlo.cpp
//  MonteCarlo
//
//  Created by Adrien Bruchet on 29/03/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

#include "EstimateurMonteCarlo.h"

#include <memory>

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


//calcule l'esperance du sup empirique
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


double minLambda(SetOfPaths const& Z, SetOfPaths const& martingales){
    
    //initialisation
    double epsilon = 1e-2;
    double l_min = -10;
    double l_max = 10;
    double min = l_min;
    double max = l_max;
    double max_it = 1e3;
    int it = 0;
    MCEstimator estim = MCEstimator();
    
    //boucle de dichotomie
    while (it < max_it && (max-min) > epsilon) {
        double d = 0.25*(3*min + max);
        double c = 0.5*(min + max);
        double e = 0.25*(3*max + min);
        
        //calcul en c
        shared_ptr<SetOfPaths> M_ptr = make_shared<SetOfPaths>(Z-martingales*c);
        estim.setPaths(M_ptr);
        double val_c = estim.computeMeanSup();
        
        //calcul en d
        M_ptr = make_shared<SetOfPaths>(Z-martingales*d);
        estim.setPaths(M_ptr);
        double val_d = estim.computeMeanSup();
        
        //calcul en e
        M_ptr = make_shared<SetOfPaths>(Z-martingales*e);
        estim.setPaths(M_ptr);
        double val_e = estim.computeMeanSup();
        
        //comparaison
        if (val_c > val_e) {
            min = c;
        }
        else if (val_d < val_c){
            max = c;
        }
        else{
            min = d;
            max = e;
        }
        it++;
        
    }
    return 0.5*(max + min);
}



