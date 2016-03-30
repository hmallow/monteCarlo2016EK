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
#include "Trajectoires.h"

class SetOfPaths{
    
public:
    SetOfPaths();
    SetOfPaths(std::vector<shared_ptr<Path>> paths);
    ~SetOfPaths();
    
private:
    std::vector<std::shared_ptr<Path>> paths;
    
};

#endif /* defined(__MonteCarlo__SetOfPaths__) */
