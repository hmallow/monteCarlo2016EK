//
//  Trajectoires.h
//  MonteCarlo
//
//  Created by Adrien Bruchet on 29/03/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

#ifndef __MonteCarlo__Trajectoires__
#define __MonteCarlo__Trajectoires__

#include <stdio.h>
#include <vector>
#include "vector.h"

//une classe pour manipuler les trajectoires
class Path {
    
public:
    Path();
    Path(std::vector<double>& points); // initier objets avec points
    ~Path();
    
    std::vector<double>& Points();
    std::vector<double> Points() const;
    
    void addPoint(double point);
    
    double getLast(); //récuperer la dernière valeur
    
private:
    std::vector<double> points;
    
};


Path operator+(Path const & P1, Path const & P2);

Path operator*(Path const & P, double const lambda);

#endif /* defined(__MonteCarlo__Trajectoires__) */
