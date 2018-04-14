//
// Created by default on 19/03/18.
//

#ifndef COMPILER_NFA_H
#define COMPILER_NFA_H


#include "Node.h"

class NFA {
public:
    vector<Node> getNfaTable();
    void setNfaTable(vector<Node>);
    Node &getStartNode();
    Node &getEndNode();
    void addNode(Node n);
    Node &getNode(int i);

private:
    vector<Node> nfaTable;
};


#endif //COMPILER_NFA_H