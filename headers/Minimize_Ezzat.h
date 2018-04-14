//
// Created by default on 13/04/18.
//

#ifndef COMPILER_MINIMIZE_EZZAT_H
#define COMPILER_MINIMIZE_EZZAT_H


#include "Node.h"

class Minimize_Ezzat {

public:
    vector<Node> graphy;
    vector<Node> minimized;
    void init_mini(vector<Node> graph);
    void partition();

    bool areEqual(vector<Node> first, vector<Node> second);

    bool equals_States(Node first, Node second, vector<Node> list);

    void copyNodes(vector<Node> from, vector<Node> &to);

    vector<Node> getMinimize();

    void collect();
};


#endif //COMPILER_MINIMIZE_EZZAT_H
