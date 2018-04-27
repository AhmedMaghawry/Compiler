//
// Created by arsanuos on 25/04/18.
//

#ifndef COMPILER_LEFTRECURSION_H
#define COMPILER_LEFTRECURSION_H

#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;

class LeftRecursion {

private:
    vector<vector<pair<string, bool>>> detect_and_delete_left_recursion(vector<vector<pair<string, bool> > > &all_choices, string all_choice_first, string new_non_terminal);
    void print_grammar(map<string, vector<vector<pair<string, bool> > > > &grammar);
public:
    map<string, vector<vector<pair<string, bool> > > > clean_left_recursion(map<string, vector<vector<pair<string, bool> > > > &grammer);
};


#endif //COMPILER_LEFTRECURSION_H
