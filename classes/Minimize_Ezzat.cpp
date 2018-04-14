//
// Created by default on 13/04/18.
//

#include <map>
#include "../headers/Minimize_Ezzat.h"

int counter = 0;
map<string, bool> mape;

Node getNode(string basic_string, vector<Node> list);

void Minimize_Ezzat::init_mini(vector<Node> graph, vector<string> symboles) {
    graphy = graph;
    for (int i = 0; i < graphy.size(); ++i) {
        graphy[i].setGroupNumber((graphy[i].getAcceptance().first == -1)? to_string(counter) : to_string(counter + 1));
    }
    counter++;
    partition();
    collect();
}

void Minimize_Ezzat::partition() {
    vector<Node> last_state;
    do{
        last_state.clear();
        copyNodes(graphy, last_state);
        for (int i = 0; i < graphy.size(); ++i) {
            for (int j = i + 1; j < graphy.size(); ++j) {
                if(last_state[i].getGroupNumber() == last_state[j].getGroupNumber()) {
                    if(equals_States(graphy[i], graphy[j], last_state)) {
                        graphy[j].setGroupNumber(graphy[i].getGroupNumber());
                    } else {
                        graphy[j].setGroupNumber(to_string(++counter));
                    }
                }
            }
        }
    } while(!areEqual(last_state, graphy));
}

bool Minimize_Ezzat::areEqual(vector<Node> first, vector<Node> second) {
    for (int i = 0; i < first.size(); ++i) {
        if (first[i].getGroupNumber() != second[i].getGroupNumber()) {
            return false;
        }
    }
    return true;
}

bool Minimize_Ezzat::equals_States(Node first, Node second, vector<Node> list) {
    for (int i = 0; i < first.getTransitions().size(); ++i) {
        if (getNode(first.getTransitions()[i].getTo(), list).getGroupNumber() != getNode(second.getTransitions()[i].getTo(), list).getGroupNumber()) {
            return false;
        }
    }
    return true;
}

void Minimize_Ezzat::copyNodes(vector<Node> from, vector<Node> &to) {
    for (Node n : from) {
        to.push_back(n);
    }
}

vector<Node> Minimize_Ezzat::getMinimize() {
    return minimized;
}

void Minimize_Ezzat::collect() {
    for (Node n : graphy) {
        if(mape.find(n.getGroupNumber()) == mape.end()) {
            mape.insert(pair<string, bool>(n.getGroupNumber(), true));
            minimized.push_back(n);
        }
    }
}
