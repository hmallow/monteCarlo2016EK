//
//  SetOfPaths.cpp
//  MonteCarlo
//
//  Created by Adrien Bruchet on 30/03/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

#include "SetOfPaths.h"

using namespace std;

SetOfPaths::SetOfPaths(SetOfPaths const& S){
    
    paths = S.getPaths();
    
}

void const SetOfPaths::addPath(Path & path){
    
    shared_ptr<Path> path_ptr = make_shared<Path>(path);
    paths.push_back(path_ptr);
}


SetOfPaths operator+(SetOfPaths const & S1, SetOfPaths const& S2){
    if (S1.getPaths().size() != S2.getPaths().size()) {
        cout << "probleme de taille !"<< endl;
    }
    std::vector<std::shared_ptr<Path>> sums;
    for (int i = 0; i < S1.getPaths().size(); i++) {
        Path sum = *(S1.getPaths()[i]) + *(S2.getPaths()[i]);
        sums.push_back(make_shared<Path>(sum));
    }
    return SetOfPaths(sums);
}


SetOfPaths operator*(SetOfPaths const& S1, double lambda){
    std::vector<std::shared_ptr<Path>> scals;
    for (int i = 0; i < S1.getPaths().size(); i++) {
        Path scal =  *(S1.getPaths()[i])*lambda;
        scals.push_back(make_shared<Path>(scal));
    }
    return SetOfPaths(scals);
}