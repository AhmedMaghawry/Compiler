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

    void emptyTransitions(string symbole);

    void setTransitions(vector<Transition> trans);

    void setGroupNumber (string groupNum);

    string getGroupNumber ();

    void setTotalGroupNumber (string totalNum);

    string getTotalGroupNumber ();
    bool operator < (const Node& e) const {
        bool result = true;
        if( (groupNumber == e.groupNumber) &&
            totalgroupNumber== e.totalgroupNumber ) {
            result = false;
        }
        return result;
    }


private:
    string name;
    pair<int, string> acceptance = {-1, "no"};
    vector<Transition> transitions;
    string groupNumber;
    string totalgroupNumber;
};


#endif //COMPILER_NODE_H