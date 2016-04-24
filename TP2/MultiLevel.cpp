//
//  MultiLevel.cpp
//  MonteCarlo
//
//  Created by Adrien Bruchet on 24/04/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

using namespace std;

#include "MultiLevel.h"


MultiLevel::MultiLevel(){
    
}

MultiLevel::MultiLevel(int L, int k, int n){
    
}

MultiLevel::~MultiLevel(){
    
}

vector<double> MultiLevel::computeTaus(Path const& PayOff, Path const& EuropeanOption){
    
    int N = PayOff.Points().size();
    vector<double> taus;
    for (int i = 0; i < N; i++) {
        bool found = false;
        int j = i;
        while (found == false||j != N) {
            if (EuropeanOption.Points()[j] <= PayOff.Points()[j]) {
                found = true;
                taus.push_back(j);
            }
            j++;
        }
    }
    return taus;
}