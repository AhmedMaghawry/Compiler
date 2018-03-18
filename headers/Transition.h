//
// Created by default on 18/03/18.
//

#ifndef COMPILER_TRANSITION_H
#define COMPILER_TRANSITION_H


#include "Node.h"

class Transition {

public:
    Transition(const Node &to, char transition);

    virtual ~Transition();

    const Node &getTo() const;

    void setTo(const Node &to);

    char getTransition() const;

    void setTransition(char transition);

private:
    Node to;
    char transition;
};


#endif //COMPILER_TRANSITION_H
