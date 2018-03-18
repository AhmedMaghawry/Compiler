//
// Created by default on 18/03/18.
//

#ifndef COMPILER_NODE_H
#define COMPILER_NODE_H


#include <vector>
#include <string>
#include "Transition.h"

using namespace std;

class Node {

public:
    Node(int number);

    virtual ~Node();
    int getNumber() const;

    void setNumber(int number);

    const vector<string> &getAcceptance() const;

    void addAcceptance(string acceptance);

    const vector<Transition> &getTransitions() const;

    void addTransitions(Transition transition);

private:
    int number;
    vector<string> acceptance;
    vector<Transition> transitions;
};


#endif //COMPILER_NODE_H
