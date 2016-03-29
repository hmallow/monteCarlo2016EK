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

class Path {
    
public:
    Path();
    Path(std::vector<double>& points);
    ~Path();
    
    std::vector<double>& setPoints();
    std::vector<double> const getPoints();
    
    
    
private:
    std::vector<double> points;
    
};

#endif /* defined(__MonteCarlo__Trajectoires__) */
