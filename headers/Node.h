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
    Node(string name);

    virtual ~Node();
    string getNumber();

    void setNumber(string number);

    vector<string> getAcceptance();

    void addAcceptance(string acceptance);

    vector<Transition> getTransitions();

    void addTransitions(Transition transition);

private:
    string name;
    vector<string> acceptance;
    vector<Transition> transitions;
};


#endif //COMPILER_NODE_H
