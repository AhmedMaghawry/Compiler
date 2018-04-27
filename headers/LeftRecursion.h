//
// Created by arsanuos on 25/04/18.
//

#ifndef COMPILER_LEFTRECURSION_H
#define COMPILER_LEFTRECURSION_H

#include <vector>
#include <string>
#include <map>

using namespace std;

class LeftRecursion {

public:
    map<string, vector<vector<pair<string, bool> > > > clean_left_recursion(map<string, vector<vector<pair<string, bool> > > > &grammer);
};


#endif //COMPILER_LEFTRECURSION_H
