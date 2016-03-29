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

std::vector<double>& Path::setPoints(){
    
    return points;
}

std::vector<double> const Path::getPoints(){
    
    return points;
}



