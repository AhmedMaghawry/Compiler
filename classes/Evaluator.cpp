//
// Created by arsanuos on 21/03/18.
//

#define eps "\\L"

#include "../headers/Evaluator.h"
#include "../headers/Construction.h"
#include <sstream>
#include <iostream>

/*
 * concatenate a and b
 */

NFA Evaluator::concat(NFA a, NFA b) {
    //ab not ba
    b = scaleUP(b, a.getNfaTable().size());
    a.getEndNode().addTransitions(Transition(std::to_string(a.getNfaTable().size()), eps));
    a = addToFirst(a, b);
    Evaluator::printGraph(a);
    return a;

}

/*
 * get a or b NFA
 *
 */

NFA Evaluator::oring(NFA a, NFA b) {
    //a | b
    Node first("0");
    a = scaleUP(a, 1);
    b = scaleUP(b, a.getNfaTable().size() + 1);
    first.addTransitions(Transition(a.getStartNode().getNumber(), eps));
    first.addTransitions(Transition(b.getStartNode().getNumber(), eps));
    Node end(Evaluator::getNewEndNodeNumber(a, b));
    a.getEndNode().addTransitions(Transition(Evaluator::getNewEndNodeNumber(a, b), eps));
    b.getEndNode().addTransitions(Transition(Evaluator::getNewEndNodeNumber(a, b), eps));
    NFA result;
    result.addNode(first);
    result = addToFirst(result, a);
    result = addToFirst(result, b);
    result.addNode(end);
    Evaluator::printGraph(result);
    return result;
}


/*
 * zero or more from NFA a
 */
NFA Evaluator::star(NFA a) {
    //a*
    a = scaleUP(a, 1);
    Node first("0");
    Node end(std::to_string(a.getNfaTable().size() + 1));
    first.addTransitions(Transition(end.getNumber(), eps));
    first.addTransitions(Transition(a.getNode(0).getNumber(), eps));
    a.getEndNode().addTransitions(Transition(end.getNumber(), eps));
    a.getEndNode().addTransitions(Transition(a.getStartNode().getNumber(), eps));
    NFA result;
    result.addNode(first);
    result = addToFirst(result, a);
    result.addNode(end);
    Evaluator::printGraph(result);
    return result;
}

/*
 * one or more from NFA a
 */

NFA Evaluator::plus(NFA a){
    //a+
    a = scaleUP(a, 1);
    Node first("0");
    Node end(std::to_string(a.getNfaTable().size() + 1));
    first.addTransitions(Transition(a.getNode(0).getNumber(), eps));
    a.getEndNode().addTransitions(Transition(end.getNumber(), eps));
    a.getEndNode().addTransitions(Transition(a.getStartNode().getNumber(), eps));
    NFA result;
    result.addNode(first);
    result = addToFirst(result, a);
    result.addNode(end);
    Evaluator::printGraph(result);
    return result;
}
/*
 * scaleup nodes' number as graph is direct acyclic graph so
 * node number i goes to node number j and j > i for all nodes.
 */

NFA Evaluator::scaleUP(NFA a, int n) {
    int newIndex = 0;
    vector<Node> graph = a.getNfaTable();
    for(int i = 0 ;i < graph.size(); i++){
        Node tmp = graph[i];
        Node nwNode(tmp.getNumber());
        for(int j = 0 ;j < tmp.getTransitions().size(); j++){
            Transition t = tmp.getTransitions()[j];
            newIndex = convert(t.getTo());
            t.setTo(std::to_string(n + newIndex));
            nwNode.addTransitions(t);
        }
        stringstream converter(tmp.getNumber());
        converter >> newIndex;
        newIndex += n;
        tmp.setNumber(std::to_string(newIndex));
        nwNode.setNumber(tmp.getNumber());
        graph[i] = nwNode;
    }
    a.setNfaTable(graph);
    return a;
}


NFA Evaluator::dash(NFA a, NFA b){
    Node start_node = a.getStartNode();
    string start = a.getStartNode().getTransitions()[0].getTransition();
    string end = b.getStartNode().getTransitions()[0].getTransition();
    for(int i = start.at(0) + 1 ;i <= end.at(0); i++){
        char tmp = i;
        string str(1, tmp);
        start_node.addTransitions(Transition(a.getEndNode().getNumber(),str));
    }
    Evaluator::printGraph(a);
    return a;
    /*string start = a.getStartNode().getTransitions()[0].getTransition();
    string end = b.getStartNode().getTransitions()[0].getTransition();
    NFA result = Construction::construct(start);
    for(int i = start.at(0) + 1 ;i <= end.at(0); i++){
        char tmp = i;
        string str(1, tmp);
        result = oring(result, Construction::construct(str));
    }
    Evaluator::printGraph(result);
    return result;*/

}

/*
 * convert string to int
 */

int Evaluator::convert(string x){
    int n = 0;
    stringstream converter(x);
    converter >> n;
    return n;
}

/*
 * add b to graph a
 */
NFA Evaluator::addToFirst(NFA a, NFA b){
    for(int i = 0 ;i < b.getNfaTable().size(); i++){
        a.addNode(b.getNode(i));
    }
    return a;
}

string Evaluator::getNewEndNodeNumber(NFA a, NFA b){
    return std::to_string(b.getNfaTable().size() + a.getNfaTable().size() + 1);
}


void Evaluator::printGraph(NFA a){
    //return;
    int newIndex = 0;
    vector<Node> graph = a.getNfaTable();
    for(int i = 0 ;i < graph.size(); i++){
        Node tmp = graph[i];
        cout<<tmp.getNumber();
        for(int j = 0 ;j < tmp.getTransitions().size(); j++){
            Transition t = tmp.getTransitions()[j];
            cout<<" "<<t.getTo()<<"("<<t.getTransition()<<")"<<" ";
        }
        cout<<endl;
    }
}