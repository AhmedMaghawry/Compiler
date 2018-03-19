//
// Created by Ezzat on 18/03/18.
//

#ifndef COMPILER_NODE_H
#define COMPILER_NODE_H


#include <vector>
#include <string>
#include "Transition.h"

using namespace std;

class Node {

public:
    Node(string number);

    virtual ~Node();
    string getNumber() const;

    void setNumber(string number);

    const vector<string> &getAcceptance() const;

    void addAcceptance(string acceptance);

    const vector<Transition> &getTransitions() const;

    void addTransitions(Transition transition);

private:
    string number;
    vector<string> acceptance;
    vector<Transition> transitions;
};


#endif //COMPILER_NODE_H
