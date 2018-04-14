//
// Created by default on 19/03/18.
//

#include "../headers/NFA.h"
#include <iostream>



vector<Node> NFA::getNfaTable() {
    return nfaTable;
}

void NFA::setNfaTable(vector<Node> newNfa){
    nfaTable = newNfa;
}

Node& NFA::getEndNode() {
    return nfaTable[nfaTable.size() - 1];
}

Node& NFA::getStartNode() {
    return nfaTable[0];
}

void NFA::addNode(Node n){
    nfaTable.push_back(n);
}

Node& NFA::getNode(int i){
    return nfaTable[i];
}
