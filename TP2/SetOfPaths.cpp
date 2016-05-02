//
//  SetOfPaths.cpp
//  MonteCarlo
//
//  Created by Adrien Bruchet on 30/03/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

#include "SetOfPaths.h"

#include <memory>

using namespace std;

SetOfPaths::SetOfPaths(){
   paths = std::vector<shared_ptr<Path>>();
}

SetOfPaths::SetOfPaths(std::vector<std::shared_ptr<Path>> new_paths){
    paths = new_paths;
}

SetOfPaths::SetOfPaths(SetOfPaths const& S){
    
    for (int i = 0; i < S.getPaths().size(); i++) {
        paths.push_back(make_shared<Path>(*(S.getPaths()[i])));
    }
}

SetOfPaths::~SetOfPaths(){
    
}

void SetOfPaths::setPaths(std::vector<std::shared_ptr<Path>>& new_paths){
    
    paths = new_paths;
}

std::vector<std::shared_ptr<Path>> SetOfPaths::getPaths() const{
    
    return paths;
}

shared_ptr<Path> SetOfPaths::getPath(int index){
    return paths[index];
}


void const SetOfPaths::addPath(Path & path){
    
    shared_ptr<Path> path_ptr = make_shared<Path>(path);
    paths.push_back(path_ptr);
}

void SetOfPaths::massConvertToPut(double strike){
    for (int i = 0; i < paths.size(); i++) {
        paths[i]->convertPut(strike);
    }
}

vector<shared_ptr<Path>> SetOfPaths::massExtractPut(double strike){
    vector<shared_ptr<Path>> set_of_puts;
    for (int i = 0; i < paths.size(); i++) {
        vector<double> points = paths[i]->extractPut(strike);
        shared_ptr<Path> put_ptr = make_shared<Path>(points);
        set_of_puts.push_back(put_ptr);
    }
    return set_of_puts;
}


//retourne un tableau des sups (1 par trajectoire)
//se base sur la methode sup de la classe Path
vector<double> SetOfPaths::computeSups() const{
    vector<double> sups;
    for (int i = 0; i < paths.size(); i++){
        sups.push_back(paths[i]->getMax());
    }
    return sups;
}


//surcharge des operateurs

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

SetOfPaths operator-(SetOfPaths const& S1, SetOfPaths const& S2){
    return S1+S2*(-1);
}