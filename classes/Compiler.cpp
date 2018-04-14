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
#include "../headers/MinimizedDFA.h"
#include "../headers/PostfixInfix.h"
#include "../headers/DFA.h"
#include "../headers/Generator.h"

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

void display_graph_temp(vector<Node> nodes) {
    for (Node node : nodes) {
        for (Transition t : node.getTransitions()) {
            cout << node.getNumber() << "-- " << t.getTransition() << " --> " << t.getTo() << endl;
        }
    }
}

int main1() {

	//NFA nfa;
	//RegexParser r;
	//r.parse_rules();
//    test3();

	DFA dfa;
	dfa.convert_from_NFA_to_DFA(graph, symbs);
    MinimizedDFA min(dfa.getDfaGraph());
    cout << "Minimized Graph -------------------->" << endl;
    vector<Node> minimized = min.evaluateMinimized();
    display_graph_temp(minimized);
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

int main() {
    /*PostfixInfix p;
    vector<string> tests;
    tests.push_back("c|d");
    tests.push_back("cd");
    tests.push_back("c+");
    tests.push_back("c*");
    tests.push_back("a-z");
    tests.push_back("c|d|e");
    for(int i = 0 ;i < tests.size(); i++){
        cout<<tests[i]<<endl;
        vector<string> t;
        for(int j = 0 ;j < tests[i].size(); j++){
            string tmp(1, tests[i][j]);
            t.push_back(tmp);
        }
        p.regular_expressions("te" + i, t);
        cout<<"-----------------------------------------------"<<endl;
    }*/

    /*PostfixInfix p;
    vector<string> tests;
    tests.push_back("Ab(c|d)");
    tests.push_back("Abbb(c|d)xyz(c|d|e|r)");
    tests.push_back("Abbb(c|d)xyz(c|d|e|r)");
    tests.push_back("Ab(c|d*)");
    tests.push_back("Ab(c|d*)+get");
    tests.push_back("A-T|543");
    tests.push_back("Ab|(c|d*)+|get");
    tests.push_back("A*b+vkhjkg");



    for(int i = 0 ;i < tests.size(); i++){
        cout<<tests[i]<<endl;
        vector<string> t;
        for(int j = 0 ;j < tests[i].size(); j++){
            string tmp(1, tests[i][j]);
            t.push_back(tmp);
        }
        string tee = "te";
        tee.append(std::to_string(i));
        p.regular_expressions(tee, t,false);
        cout<<"-----------------------------------------------"<<endl;
    }

    p.collect();*/
    /*
    DFA dfa;
    dfa.convert_from_NFA_to_DFA(p.get_NFA().getNfaTable(), p.get_symbol_table());
    MinimizedDFA min(dfa.getDfaGraph());
    cout << "Minimized Graph -------------------->" << endl;
    vector<Node> minimized = min.evaluateMinimized();
    display_graph_temp(minimized);*/
    //vector<string> t;
    //t.push_back("te");
    //t.push_back("+");
    //t.push_back("test");

    //t.push_back("*");
    //p.regular_expressions("hdl", t);
    /*PostfixInfix p;
    vector<string> tests;
    tests.push_back("A*");



    for(int i = 0 ;i < tests.size(); i++){
        cout<<tests[i]<<endl;
        vector<string> t;
        for(int j = 0 ;j < tests[i].size(); j++){
            string tmp(1, tests[i][j]);
            t.push_back(tmp);
        }
        p.regular_definitions("te", t);
        cout<<"-----------------------------------------------"<<endl;
    }
    vector<string> t;
    t.push_back("te");
    t.push_back("*");
    p.regular_expressions("hdk",t);*/

    /*PostfixInfix p;
    vector<string> tests;
    tests.push_back("Ab(c|d)");
    for(int i = 0 ;i < tests.size(); i++){
        cout<<tests[i]<<endl;
        vector<string> t;
        for(int j = 0 ;j < tests[i].size(); j++){
            string tmp(1, tests[i][j]);
            t.push_back(tmp);
        }
        string tee = "te";
        tee.append(std::to_string(i));
        p.regular_expressions(tee, t,false);
        cout<<"-----------------------------------------------"<<endl;
    }
    p.collect();
    NFA a = p.get_NFA();*/




    /*DFA dfa;
    dfa.convert_from_NFA_to_DFA(a.getNfaTable(), r.get_symbol_table());
    vector<Node> m = dfa.getDfaGraph();
    //MinimizedDFA min(m);
    cout << "Minimized Graph -------------------->" << endl;
    //vector<Node> minimized = min.evaluateMinimized();
    //display_graph_temp(minimized);
    Generator g;
    g.START_NODE = stoi(m[0].getNumber());
    g.dfa = dfa.get_saeed_array(m);
    g.lexal_analizer_run();*/

    //write the regular expression you want in the file input.txt
    /*RegexParser r;
    NFA a = r.parse_rules();*/


    PostfixInfix p;
    vector<string> tests;
    tests.push_back("Ab(c|d)");
    tests.push_back("Abbb(c|d)xyz(c|d|e|r)");
    tests.push_back("Abbb(c|d)xyz(c|d|e|r)");
    tests.push_back("Ab(c|d*)");
    tests.push_back("Ab(c|d*)+get");
    tests.push_back("A-T|543");
    tests.push_back("Ab|(c|d*)+|get");
    tests.push_back("A*b+vkhjkg");



    for(int i = 0 ;i < tests.size(); i++){
        cout<<tests[i]<<endl;
        vector<string> t;
        for(int j = 0 ;j < tests[i].size(); j++){
            string tmp(1, tests[i][j]);
            t.push_back(tmp);
        }
        string tee = "te";
        tee.append(std::to_string(i));
        p.regular_expressions(tee, t,false);
        cout<<"-----------------------------------------------"<<endl;
    }

    p.collect();
    NFA n = p.get_NFA();

    return 0;
}