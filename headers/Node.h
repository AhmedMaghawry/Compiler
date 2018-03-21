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

    pair<int,string> getAcceptance();

    void addAcceptance(pair<int, string> acceptance);

    vector<Transition> getTransitions();

    void addTransitions(Transition transition);

private:
    string name;
    pair<int, string> acceptance = {-1, "no"};
    vector<Transition> transitions;
};


#endif //COMPILER_NODE_H
