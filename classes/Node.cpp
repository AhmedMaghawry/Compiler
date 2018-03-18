//
// Created by Ezzat on 18/03/18.
//

#include "../headers/Node.h"

Node::Node(int number) : number(number) {}

Node::~Node() {

}

int Node::getNumber() const {
    return number;
}

void Node::setNumber(int number) {
    Node::number = number;
}

const vector<string> &Node::getAcceptance() const {
    return acceptance;
}

void Node::addAcceptance(string acceptance) {
    Node::acceptance.push_back(acceptance);
}

const vector<Transition> &Node::getTransitions() const {
    return transitions;
}

void Node::addTransitions(Transition transition) {
    Node::transitions.push_back(transition);
}
