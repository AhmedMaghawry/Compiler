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
#include "../headers/Generator.h"
#include "../headers/Minimize_Ezzat.h"
//#include "../headers/Generator.h"

using namespace std;

vector<Node> graph;
vector<string> symbs;

void addLettersToSymboles() {
    for (int i = 0; i < 26; ++i) {
        char c = i + 97;
        string res = "c";
        res[0] = c;
        symbs.push_back(res);
    }
}

void addLettersToNode(Node &node, const char to[]) {
    for (int i = 0; i < 26; ++i) {
        char c = i + 97;
        string res = "c";
        res[0] = c;
        Transition t(to, res);
        node.addTransitions(t);
    }
    Transition t(to, "A");
    Transition t1(to, "B");
    Transition t2(to, "C");
    Transition t3(to, "D");
    Transition t4(to, "E");
    Transition t5(to, "F");
    node.addTransitions(t);
    node.addTransitions(t1);
    node.addTransitions(t2);
    node.addTransitions(t3);
    node.addTransitions(t4);
    node.addTransitions(t5);
}

void addDigitsToSymboles() {
    for(int i = 0; i < 10; i++) {
        symbs.push_back(to_string(i));
    }
}

void addDigitsToNode(Node &node, const char to[]) {
    for(int i = 0; i < 10; i++) {
        Transition t(to, to_string(i));
        node.addTransitions(t);
    }
}
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
    Node P("1");
    Node R("2");
    Node Q("3");
    Transition tP1("2","\\L");
    Transition tP2("2", "c");
    Transition tP3("3","\\L");
    Transition tP4("3", "b");
    Transition tQ1("1", "a");
    //Transition tQ2("P", "c");
    Transition tQ3("3", "c");
    Transition tQ4("2", "b");
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

void test4() {
    Node P("1");
    Node R("2");
    Transition tP1("2","\\L");
    Transition tP2("1", "\\L");
    Transition tR1("1", "\\L");
    Transition tR2("1", "\\L");
    Transition tR3("2", "\\L");
    P.addTransitions(tP1);
    P.addTransitions(tP2);
    R.addTransitions(tR1);
    R.addTransitions(tR2);
    R.addTransitions(tR3);
    R.addAcceptance({1,"if"});
    graph.push_back(P);
    graph.push_back(R);
    symbs.push_back("a");
    symbs.push_back("b");
    symbs.push_back("c");
}

void test5() {
    Node n1("1");
    Node n2("2");
    Node n3("3");
    Node n4("4");
    Transition t12("2","\\L");
    Transition t14("4", "\\L");
    Transition t23("3", "a");
    Transition t32("2", "\\L");
    Transition t34("4", "\\L");
    n1.addTransitions(t12);
    n1.addTransitions(t14);
    n2.addTransitions(t23);
    n3.addTransitions(t32);
    n3.addTransitions(t34);
    n4.addAcceptance({1,"if"});
    graph.push_back(n1);
    graph.push_back(n2);
    graph.push_back(n3);
    graph.push_back(n4);
    symbs.push_back("a");
    symbs.push_back("b");
    symbs.push_back("c");
}

void test6() {
    Node n1("1");
    Node n2("2");
    Node n3("3");
    Node n4("4");
    Transition t11("1","a");
    Transition t112("1", "b");
    Transition t12("2", "a");
    Transition t23("3", "b");
    Transition t34("4", "b");
    n1.addTransitions(t12);
    n1.addTransitions(t11);
    n1.addTransitions(t112);
    n2.addTransitions(t23);
    n3.addTransitions(t34);
    n4.addAcceptance({1,"if"});
    graph.push_back(n1);
    graph.push_back(n2);
    graph.push_back(n3);
    graph.push_back(n4);
    symbs.push_back("a");
    symbs.push_back("b");
}

void test6_withE() {
    Node n1("1");
    Node n2("2");
    Node n3("3");
    Node n4("4");
    Node n5("5");
    Node n6("6");
    Node n7("7");
    Node n8("8");
    Node n9("9");
    Node n10("10");
    Node n11("11");
    Transition t12("2","\\L");
    Transition t18("8", "\\L");
    Transition t23("3", "\\L");
    Transition t25("5", "\\L");
    Transition t34("4","a");
    Transition t56("6", "b");
    Transition t47("7", "\\L");
    Transition t67("7", "\\L");
    Transition t72("2","\\L");
    Transition t78("8", "\\L");
    Transition t89("9", "a");
    Transition t910("10", "b");
    Transition t1011("11", "b");
    n11.addAcceptance({1,"if"});
    n1.addTransitions(t12);
    n1.addTransitions(t18);
    n2.addTransitions(t23);
    n2.addTransitions(t25);
    n3.addTransitions(t34);
    n5.addTransitions(t56);
    n4.addTransitions(t47);
    n6.addTransitions(t67);
    n7.addTransitions(t72);
    n7.addTransitions(t78);
    n8.addTransitions(t89);
    n9.addTransitions(t910);
    n10.addTransitions(t1011);
    graph.push_back(n1);
    graph.push_back(n2);
    graph.push_back(n3);
    graph.push_back(n4);
    graph.push_back(n5);
    graph.push_back(n6);
    graph.push_back(n7);
    graph.push_back(n8);
    graph.push_back(n9);
    graph.push_back(n10);
    graph.push_back(n11);
    symbs.push_back("a");
    symbs.push_back("b");
}

void test7() {
    Node n1("1");
    Node n2("2");
    Node n3("3");
    Node n4("4");
    Node n5("5");
    Node n6("6");
    Node n7("7");
    Node n8("8");
    Node n9("9");
    Node n10("10");
    Node n11("11");
    Node n12("12");
    Node n13("13");
    Node n14("14");
    Node n15("15");
    Transition t12("2","\\L");
    Transition t15("5", "\\L");
    Transition t18("8","\\L");
    Transition t111("11", "\\L");
    Transition t113("13","\\L");
    n1.addTransitions(t12);
    n1.addTransitions(t15);
    n1.addTransitions(t18);
    n1.addTransitions(t111);
    n1.addTransitions(t113);
    Transition t23("3", "b");
    n2.addTransitions(t23);
    Transition t34("4", "0");
    Transition t34_("4", "1");
    n3.addTransitions(t34);
    n3.addTransitions(t34_);
    Transition t44("4", "0");
    Transition t44_("4", "1");
    n4.addTransitions(t44);
    n4.addTransitions(t44_);
    n4.addAcceptance({1,"bin"});
    Transition t56("6", "o");
    n5.addTransitions(t56);
    Transition t67("7", "0");
    Transition t67_("7", "1");
    Transition t67_2("7", "2");
    Transition t67_3("7", "3");
    Transition t67_4("7", "4");
    Transition t67_5("7", "5");
    Transition t67_6("7", "6");
    Transition t67_7("7", "7");
    n6.addTransitions(t67);
    n6.addTransitions(t67_);
    n6.addTransitions(t67_2);
    n6.addTransitions(t67_3);
    n6.addTransitions(t67_4);
    n6.addTransitions(t67_5);
    n6.addTransitions(t67_6);
    n6.addTransitions(t67_7);
    Transition t77("7", "0");
    Transition t77_("7", "1");
    Transition t77_2("7", "2");
    Transition t77_3("7", "3");
    Transition t77_4("7", "4");
    Transition t77_5("7", "5");
    Transition t77_6("7", "6");
    Transition t77_7("7", "7");
    n7.addTransitions(t77);
    n7.addTransitions(t77_);
    n7.addTransitions(t77_2);
    n7.addTransitions(t77_3);
    n7.addTransitions(t77_4);
    n7.addTransitions(t77_5);
    n7.addTransitions(t77_6);
    n7.addTransitions(t77_7);
    n7.addAcceptance({2,"oct"});
    Transition t89("9", "h");
    n8.addTransitions(t89);
    Transition t910("10", "A");
    Transition t910_1("10", "B");
    Transition t910_2("10", "C");
    Transition t910_3("10", "D");
    Transition t910_4("10", "E");
    Transition t910_5("10", "F");
    n9.addTransitions(t910);
    n9.addTransitions(t910_1);
    n9.addTransitions(t910_2);
    n9.addTransitions(t910_3);
    n9.addTransitions(t910_4);
    n9.addTransitions(t910_5);
    addDigitsToNode(n9, "10");
    Transition t1010("10", "A");
    Transition t1010_1("10", "B");
    Transition t1010_2("10", "C");
    Transition t1010_3("10", "D");
    Transition t1010_4("10", "E");
    Transition t1010_5("10", "F");
    n10.addTransitions(t1010);
    n10.addTransitions(t1010_1);
    n10.addTransitions(t1010_2);
    n10.addTransitions(t1010_3);
    n10.addTransitions(t1010_4);
    n10.addTransitions(t1010_5);
    addDigitsToNode(n10, "10");
    n10.addAcceptance({3,"hex"});
    addDigitsToNode(n11, "12");
    addDigitsToNode(n12, "12");
    n12.addAcceptance({4,"intconst"});
    addLettersToNode(n13, "14");
    addLettersToNode(n14, "15");
    addDigitsToNode(n14, "15");
    addLettersToNode(n15, "15");
    addDigitsToNode(n15, "15");
    n15.addAcceptance({5,"id"});
    graph.push_back(n1);
    graph.push_back(n2);
    graph.push_back(n3);
    graph.push_back(n4);
    graph.push_back(n5);
    graph.push_back(n6);
    graph.push_back(n7);
    graph.push_back(n8);
    graph.push_back(n9);
    graph.push_back(n10);
    graph.push_back(n11);
    graph.push_back(n12);
    graph.push_back(n13);
    graph.push_back(n14);
    graph.push_back(n15);
    symbs.push_back("A");
    symbs.push_back("B");
    symbs.push_back("C");
    symbs.push_back("D");
    symbs.push_back("E");
    symbs.push_back("F");
    addLettersToSymboles();
    addDigitsToSymboles();
}

void test8() {
    Node n1("1");
    Node n2("2");
    Node n3("3");
    Node n4("4");
    Node n5("5");
    Transition t11("1","0");
    Transition t12("2", "0");
    Transition t13("3", "0");
    Transition t14("4", "0");
    Transition t14_1("4", "1");
    Transition t15("5", "0");
    Transition t15_1("5", "1");
    Transition t23("3", "0");
    Transition t25("5", "1");
    Transition t32("2", "1");
    Transition t45("5","0");
    n5.addAcceptance({1,"if"});
    n1.addTransitions(t11);
    n1.addTransitions(t12);
    n1.addTransitions(t13);
    n1.addTransitions(t14);
    n1.addTransitions(t14_1);
    n1.addTransitions(t15);
    n1.addTransitions(t15_1);
    n2.addTransitions(t23);
    n2.addTransitions(t25);
    n3.addTransitions(t32);
    n4.addTransitions(t45);
    graph.push_back(n1);
    graph.push_back(n2);
    graph.push_back(n3);
    graph.push_back(n4);
    graph.push_back(n5);
    symbs.push_back("0");
    symbs.push_back("1");
}

void test9() {
    Node n1("1");
    Node n2("2");
    Node n3("3");
    Node n4("4");
    Node n5("5");
    Node n6("6");
    Transition t12("2","0");
    Transition t13("3", "1");
    Transition t21("1", "0");
    Transition t24("4", "1");
    Transition t35("5","0");
    Transition t36("6", "1");
    Transition t45("5", "0");
    Transition t46("6", "1");
    Transition t55("5", "0");
    Transition t56("6", "1");
    Transition t66("6", "0");
    Transition t66_1("6", "1");
    n3.addAcceptance({1,"if"});
    n4.addAcceptance({2,"if2"});
    n5.addAcceptance({3,"if3"});
    n1.addTransitions(t12);
    n1.addTransitions(t13);
    n2.addTransitions(t21);
    n2.addTransitions(t24);
    n3.addTransitions(t35);
    n3.addTransitions(t36);
    n4.addTransitions(t45);
    n4.addTransitions(t46);
    n5.addTransitions(t55);
    n5.addTransitions(t56);
    n6.addTransitions(t66);
    n6.addTransitions(t66_1);
    graph.push_back(n1);
    graph.push_back(n2);
    graph.push_back(n3);
    graph.push_back(n4);
    graph.push_back(n5);
    graph.push_back(n6);
    symbs.push_back("0");
    symbs.push_back("1");
}

void display_graph_temp(vector<Node> nodes) {
    for (Node node : nodes) {
        for (Transition t : node.getTransitions()) {
            cout << node.getNumber() << "-- " << t.getTransition() << " --> " << t.getTo() << "--" << node.getAcceptance().second << "--" << node.getGroupNumber() << endl;
        }
    }
}

int main_() {
    test8();
	DFA dfa;
	dfa.convert_from_NFA_to_DFA(graph, symbs);
    //MinimizedDFA min(dfa.getDfaGraph());
    cout << "Minimized Graph -------------------->" << endl;
    //vector<Node> minimized = min.evaluateMinimized();
    Minimize_Ezzat m;
    m.init_mini(dfa.getDfaGraph(), symbs);
    display_graph_temp(m.getMinimize());
    return 0;
}

int main() {
    test9();
    Minimize_Ezzat m;
    m.init_mini(graph, symbs);
    display_graph_temp(m.getMinimize());
    return 0;
}

int main2() {
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
    DFA dfa;
    dfa.convert_from_NFA_to_DFA(n.getNfaTable(), p.get_symbol_table());
    return 0;
}
