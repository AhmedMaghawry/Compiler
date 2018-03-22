//============================================================================
// Name        : Compiler.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<bits/stdc++.h>
#include "../headers/RegexParser.h"
#include "../headers/Node.h"
#include "../headers/DFA.h"

using namespace std;

vector<Node> graph;
vector<string> symbs;

void test1() {
    Node A("A");
    Node B("B");
    Node C("C");
    Transition tA1("A","0");
    Transition tA2("B", "\\L");
    Transition tB1("B", "1");
    Transition tB2("C", "\\L");
    Transition tC1("C", "0");
    Transition tC2("C", "1");
    A.addTransitions(tA1);
    A.addTransitions(tA2);
    B.addTransitions(tB1);
    B.addTransitions(tB2);
    C.addTransitions(tC1);
    C.addTransitions(tC2);
    C.addAcceptance({1,"if"});
    graph.push_back(A);
    graph.push_back(B);
    graph.push_back(C);
    symbs.push_back("0");
    symbs.push_back("1");
}

void test2() {
                Node A("A");
                Node B("B");
                Node C("C");
                Node D("D");
                Transition tA1("B","0");
                Transition tB1("B", "1");
                Transition tB2("C", "\\L");
                Transition tC1("C", "0");
                Transition tC2("D", "1");
                A.addTransitions(tA1);
                B.addTransitions(tB1);
                B.addTransitions(tB2);
                C.addTransitions(tC1);
                C.addTransitions(tC2);
                D.addAcceptance({1,"if"});
                graph.push_back(A);
                graph.push_back(B);
                graph.push_back(C);
                graph.push_back(D);
                symbs.push_back("0");
                symbs.push_back("1");
}

void test3() {
    Node P("P");
    Node R("R");
    Node Q("Q");
    Transition tP1("R","\\L");
    Transition tP2("R", "c");
    Transition tP3("Q","\\L");
    Transition tP4("Q", "b");
    Transition tQ1("P", "a");
    //Transition tQ2("P", "c");
    Transition tQ3("Q", "c");
    Transition tQ4("R", "b");
    P.addTransitions(tP1);
    P.addTransitions(tP2);
    P.addTransitions(tP3);
    P.addTransitions(tP4);
    Q.addTransitions(tQ1);
    //Q.addTransitions(tQ2);
    Q.addTransitions(tQ3);
    Q.addTransitions(tQ4);
    R.addAcceptance({1,"if"});
    graph.push_back(P);
    graph.push_back(Q);
    graph.push_back(R);
    symbs.push_back("a");
    symbs.push_back("b");
    symbs.push_back("c");
}

int main() {

	//NFA nfa;
	//RegexParser r;
	//r.parse_rules();
    test3();
	DFA dfa;
	dfa.convert_from_NFA_to_DFA(graph, symbs);
	//DFA dfa;
	//dfa.convert_from_NFA_to_DFA(nfa.getNfaTable());
	//Generator generator;
	//generator.run(dfa.getDfaGraph());
//	Reader R1 ;
//
//	    R1.readFiletoLines("input.txt");
//
//	    vector <string> ans  = R1.readingLines;
//	    Writer W1 ;
//	    W1.writeLinesToFile("output.txt",ans);
	    return 0;
}
