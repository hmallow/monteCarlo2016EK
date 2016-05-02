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
//#include "vector.h"
#include <math.h>

//une classe pour manipuler les trajectoires
class Path {
    
public:
    Path();
    Path(std::vector<double>& new_points); // initier objets avec points
    Path(Path const& traj);
    ~Path();
    
    std::vector<double>& Points();
    std::vector<double> Points() const;
    
    double getPoint(int index) const;
    
    void addPoint(double point);
    
    void convertPut(double strike);
    std::vector<double> extractPut(double strike) const;
    
    void discountPath(double T, double r);
    
    double getLast(); //récuperer la dernière valeur
    double getMax(int a=0);
    
private:
    std::vector<double> points;
    int N;
    
};

//Path convertPut(Path & path, double strike);

Path operator+(Path const & P1, Path const & P2);

Path operator*(Path const & P, double const lambda);

Path operator-(Path const & P, Path const & P2);

#endif /* defined(__MonteCarlo__Trajectoires__) */
