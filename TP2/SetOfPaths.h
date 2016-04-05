//
//  SetOfPaths.h
//  MonteCarlo
//
//  Created by Adrien Bruchet on 30/03/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

#ifndef __MonteCarlo__SetOfPaths__
#define __MonteCarlo__SetOfPaths__

#include <stdio.h>
#include <iostream>
#include "Trajectoires.h"
#include <memory>

class SetOfPaths{
    
public:
    SetOfPaths();
    SetOfPaths(std::vector<std::shared_ptr<Path>> new_paths);
    SetOfPaths(SetOfPaths const &S);
    ~SetOfPaths();
    
    void setPaths(std::vector<std::shared_ptr<Path>>& new_paths);
    std::vector<std::shared_ptr<Path>> getPaths() const;
    
    void const addPath(Path & path);
    
    std::vector<double> computeSups() const;
    
private:
    std::vector<std::shared_ptr<Path>> paths;
    
};

SetOfPaths operator+(SetOfPaths const & S1, SetOfPaths const& S2);
SetOfPaths operator*(SetOfPaths const& S1, double lambda);
SetOfPaths operator-(SetOfPaths const& S1, SetOfPaths const& S2);

#endif /* defined(__MonteCarlo__SetOfPaths__) */
