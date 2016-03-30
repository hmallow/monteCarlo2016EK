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

double Path:: getMax(){
    return *max_element(points.begin(), points.end());
    
}

Path operator+(Path const & P1, Path const & P2){
    
    vector<double> sum;
    for (int i = 0; i < P1.Points().size(); i++) {
        sum.push_back(P1.Points()[i] + P2.Points()[i]);
    }
    return Path(sum);
}

Path operator*(Path const & P, double const lambda){
    vector<double> scal;
    for (int i = 0; i < P.Points().size(); i++) {
        scal.push_back(lambda*P.Points()[i]);
    }
    return Path(scal);
}

