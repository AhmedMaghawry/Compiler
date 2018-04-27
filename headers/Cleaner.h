//
// Created by arsanuos on 25/04/18.
//

#ifndef COMPILER_CLEANER_H
#define COMPILER_CLEANER_H

#include <vector>
#include <string>
#include <map>

using namespace std;

class Cleaner {

public:
    map<string, vector<vector<pair<string, bool> > > > clean(map<string, vector<vector<pair<string, bool> > > > &grammer);
};


#endif //COMPILER_CLEANER_H
