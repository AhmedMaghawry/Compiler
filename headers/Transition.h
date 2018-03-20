//
// Created by Ezzat on 18/03/18.
//

#include <vector>
#include <string>

#ifndef COMPILER_TRANSITION_H
#define COMPILER_TRANSITION_H

using namespace std;

class Transition {

public:
    Transition(string to, string transition);

    virtual ~Transition();

    string getTo();

    void setTo(string to);

    string getTransition();

    void setTransition(string transition);

private:
    string to;
    string transition;
};


#endif //COMPILER_TRANSITION_H
