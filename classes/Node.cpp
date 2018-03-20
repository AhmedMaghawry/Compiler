//
// Created by Ezzat on 18/03/18.
//

#include "../headers/Node.h"

Node::Node(string name) : name(name) {}

Node::~Node() {

}

string Node::getNumber() {
    return name;
}

void Node::setNumber(string number) {
    Node::name = number;
}

vector<string> Node::getAcceptance() {
    return acceptance;
}

void Node::addAcceptance(string acceptance) {
    Node::acceptance.push_back(acceptance);
}

vector<Transition> Node::getTransitions() {
    return transitions;
}

void Node::addTransitions(Transition transition) {
    Node::transitions.push_back(transition);
}
