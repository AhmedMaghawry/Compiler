//
// Created by default on 19/03/18.
//

#ifndef COMPILER_NFA_H
#define COMPILER_NFA_H


#include "Node.h"

class NFA {

public:
    const vector<Node> &getNfaTable() const;

private:
    vector<Node> nfaTable;

};


#endif //COMPILER_NFA_H
