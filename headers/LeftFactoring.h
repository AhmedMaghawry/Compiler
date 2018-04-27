//
// Created by arsanuos on 25/04/18.
//

#ifndef COMPILER_LEFTFACTORING_H
#define COMPILER_LEFTFACTORING_H

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

class LeftFactoring {

private:
    string get_common_in_position_zero(vector<vector<pair<string, bool>>> &all_choices, vector<vector<pair<string, bool>>> &new_line_choices);
    void print_grammar(map<string, vector<vector<pair<string, bool> > > > &grammar);
    map<string, vector<vector<pair<string, bool>>>>  immediate_left_factoring(map<string, vector<vector<pair<string, bool>>>> &grammar, bool &try_again);
    void modify_current_terminals(string str, vector<vector<pair<string, bool>>> &choices, string new_string);

public:
    map<string, vector<vector<pair<string, bool> > > > factor(map<string, vector<vector<pair<string, bool> > > > grammar);

};


#endif //COMPILER_LEFTFACTORING_H
