//
// Created by default on 18/03/18.
//

#include "../headers/Transition.h"

Transition::Transition(const Node &to, char transition) : to(to), transition(transition) {}

Transition::~Transition() {

}

const Node &Transition::getTo() const {
    return to;
}

void Transition::setTo(const Node &to) {
    Transition::to = to;
}

char Transition::getTransition() const {
    return transition;
}

void Transition::setTransition(char transition) {
    Transition::transition = transition;
}
