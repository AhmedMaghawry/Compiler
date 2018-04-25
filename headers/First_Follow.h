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
    map<string, vector<pair<string, vector<pair<string, bool>>>>> getFirstMap();
    map<string, vector<string>> getFollowMap();

private:
    const string e ="\\L";
    map<string, vector<vector<pair<string, bool>>>> grammer;
    vector<string> n_terminals;
    vector<string> terminals;
    map<string, set<pair<string, vector<pair<string, bool>>>>> firstMap;
    map<string, set<string>> followMap;
    set<pair<string, vector<pair<string, bool>>>> First(string name);
    set<string> Follow(string name);
    void concat(set<string> &res, set<string> add);
    void concat(set<pair<string, vector<pair<string, bool>>>> &res, set<pair<string, vector<pair<string, bool>>>> add);
    set<pair<string, vector<pair<string, bool>>>> repair_for_e(set<pair<string, vector<pair<string, bool>>>> vals, vector<pair<string, bool>> symboles);
    set<string> replace_e_for_follow(set<pair<string, vector<pair<string, bool>>>> li, string rule);
};


#endif //COMPILER_FIRST_FOLLOW_H