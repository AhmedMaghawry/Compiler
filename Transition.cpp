//
// Created by Ezzat on 18/03/18.
//

#include "../headers/Transition.h"

Transition::Transition(string to, string transition) : to(to), transition(transition) {}

Transition::~Transition() {

}

string Transition::getTo() {
    return to;
}

void Transition::setTo(string to) {
    Transition::to = to;
}

string Transition::getTransition() {
    return transition;
}

void Transition::setTransition(string transition) {
    Transition::transition = transition;
}
