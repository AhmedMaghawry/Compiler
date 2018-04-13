//
// Created by arsanuos on 21/03/18.
//
#define eps "\\L"

#include "../headers/Construction.h"
#include <iostream>

NFA Construction::construct(string exp) {
    if(exp.size() != 1 && exp != eps){
        throw "Non valid input form construct method long expression";
    }
    //make 2 node and set nfa then retrun nfa created.
    NFA nfa;
    vector<Node> nfatable = nfa.getNfaTable();
    Node n1("0");
    n1.addTransitions(Transition("1", exp));
    Node n2("1");
    nfatable.push_back(n1);
    nfatable.push_back(n2);
    nfa.setNfaTable(nfatable);
    return nfa;

}