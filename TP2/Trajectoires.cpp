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

Path::Path(vector<double>& new_points){
    
    points = new_points;
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

void Path::convertPut(double strike){
    
    for(int i = 0; i < points.size();i++){
        if (strike - points[i] > 0) {
            points[i] = strike - points[i];
        }
        else{
            points[i] = 0;
        }
    }
}


double Path::getLast(){
    
    return points.back();

}

double Path:: getMax(){
    double max = points[0];
    for (auto element : points){
        if (element > max) {
            max = element;
        }
    }
    return max;
}

/*Path converPut(Path & path, double strike){
    vector<double> points;
    for (double point : path.Points()) {
        double new_point = (strike-point > 0 ?strike - point:0);
    }
    Path putPath = Path(points);
    return putPath;
}*/

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

