//
//  Trajectoires.cpp
//  MonteCarlo
//
//  Created by Adrien Bruchet on 29/03/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

#include "Trajectoires.h"

using namespace std;

Path::Path(){
    
}

Path::Path(vector<double>& points){
    
    points = points;
}

Path::~Path(){
    
}

std::vector<double>& Path::Points(){
    
    return points;
}

std::vector<double> Path::Points() const{
    
    return points;
}

void Path::addPoint(double point){
    
    points.push_back(point);
    
}

double Path::getLast(){
    
    return points.back();

}

Path operator+(Path const & P1, Path const & P2){
    
    vector<double> sum = P1.Points() + P2.Points();
    return Path(sum);
}

Path operator*(Path const & P, double const lambda){
    vector<double> scal = lambda*P.Points();
    return Path(scal);
}

