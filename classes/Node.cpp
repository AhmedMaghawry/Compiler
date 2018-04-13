//
// Created by Ezzat on 18/03/18.
//

#include "../headers/Node.h"
Node::Node(string name) : name(name) {
    groupNumber="-1";
    totalgroupNumber="";
}

Node::~Node() {

}

string Node::getNumber() {
    return name;
}

void Node::setNumber(string number) {
    Node::name = number;
}

pair<int, string> Node::getAcceptance() {
    return acceptance;
}

void Node::addAcceptance(pair<int, string> acceptance) {
    pair<int, string> current_acc = getAcceptance();

    if (acceptance.first == -1)
        return;

    if (current_acc.first == -1 || current_acc.first > acceptance.first)
        Node::acceptance = acceptance;
}

vector<Transition> Node::getTransitions() {
    return transitions;
}

void Node::addTransitions(Transition transition) {
    for(Transition t : transitions) {
        if(t.getTo() == transition.getTo() && t.getTransition() == transition.getTransition())
            return;
    }
    Node::transitions.push_back(transition);
}

void Node::emptyTransitions(string symbole) {
    for (int i = 0; i < transitions.size(); i++) {
        if (transitions[i].getTransition() == symbole) {
            transitions.erase(transitions.begin() + i);
            i--;
        }
    }
}
void Node::setGroupNumber (string groupNum){
    groupNumber=groupNum;
}

string Node::getGroupNumber (){
    return groupNumber;
}

void Node::setTotalGroupNumber(string totalNum) {
    totalgroupNumber=totalNum;
}

string Node::getTotalGroupNumber (){
    return  totalgroupNumber;
}

void Node::setTransitions(vector<Transition> trans) {
    transitions = trans;
}