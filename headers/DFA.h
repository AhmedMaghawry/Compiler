//
// Created by default on 19/03/18.
//

#ifndef COMPILER_DFA_H
#define COMPILER_DFA_H


#include "Node.h"

class DFA {

public:
    vector<Node> getDfaGraph();
    void convert_from_NFA_to_DFA(vector<Node> nfaGraph, vector<string> symbs);
    void setDfaGraph(vector<Node> dfaGraph);

private:
    vector<Node> dfaGraph;

    void run_dfa(vector<Node> &final_graph, vector<Node> nfa_without_clousre);

    Node create_new_node(string basic_string, vector<Node> vector);

    void add_temp_trans(Node &node, vector<Node> vector);

    bool isExsist(Node node, queue<Node> pVector);

    void removeRedundant(vector<Node> &list);
};


#endif //COMPILER_DFA_H
