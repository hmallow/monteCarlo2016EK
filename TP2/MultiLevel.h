//
//  MultiLevel.h
//  MonteCarlo
//
//  Created by Adrien Bruchet on 24/04/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

#ifndef __MonteCarlo__MultiLevel__
#define __MonteCarlo__MultiLevel__

#include <stdio.h>
#include <vector>


class MultiLevel{
    
public:
    MultiLevel();
    MultiLevel(int L, int k, int n);
    ~MultiLevel();
    
private:
    int NbLevels;
    std::vector<int> k_L;
    std::vector<int> n_L;
    
};

#endif /* defined(__MonteCarlo__MultiLevel__) */