//
// Created by arsanuos on 21/03/18.
//

#ifndef COMPILER_CONSTRUCTION_H
#define COMPILER_CONSTRUCTION_H

#include "NFA.h"
#include <string>

using namespace std;

class Construction {

public:

    static NFA construct(string exp);

};


#endif //COMPILER_CONSTRUCTION_H
