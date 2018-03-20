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

using namespace std;

//vector <int >x;
int main() {

	//NFA nfa;
	RegexParser r;
	r.parse_rules();
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
