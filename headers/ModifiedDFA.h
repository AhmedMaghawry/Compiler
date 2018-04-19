//
// Created by default on 16/04/18.
//

#ifndef COMPILER_MODIFIEDDFA_H
#define COMPILER_MODIFIEDDFA_H


#include <queue>
#include "Node.h"

class ModifiedDFA {

public:
    ModifiedDFA();
    vector<Node> getDfaGraph();
    void convert_from_NFA_to_DFA(vector<Node> nfaGraph, vector<string> symbs, map<pair<string, string>, vector<string>> tr);
    static bool isExsist_in_list(Node node, vector<Node> list);

private:
    string sort_name(string basic_string);
    void display_map(vector<string> sy);

    vector<Node> convertMaptoGraph(vector<string> sym);

    bool isExsi(vector<Node> list, map<string, vector<Node>> all);

    string getName(vector<Node> list);

    pair<int, string> getAcc(vector<Node> vector);
};


#endif //COMPILER_MODIFIEDDFA_H
