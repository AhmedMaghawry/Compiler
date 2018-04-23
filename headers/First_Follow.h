//
// Created by default on 23/04/18.
//

#ifndef COMPILER_FIRST_FOLLOW_H
#define COMPILER_FIRST_FOLLOW_H

#include <bits/stdc++.h>

using namespace std;

class First_Follow {

public:
    First_Follow(map<string, vector<vector<pair<string, bool>>>> grammer, vector<string> n_terminals, vector<string> terminals);
    void calculate_firsts();
    void calculate_follows();
    map<string, vector<string>> getFirstMap();
    map<string, vector<string>> getFollowMap();

private:
    const string e ="\\L";
    map<string, vector<vector<pair<string, bool>>>> grammer;
    vector<string> n_terminals;
    vector<string> terminals;
    map<string, set<string>> firstMap;
    map<string, set<string>> followMap;
    set<string> First(string name);
    set<string> Follow(string name);
    void concat(set<string> &res, set<string> add);
    set<string> repair_for_e(set<string> vals, vector<pair<string, bool>> symboles);
    set<string>replace_e_for_follow(set<string> li, string rule);
};


#endif //COMPILER_FIRST_FOLLOW_H
