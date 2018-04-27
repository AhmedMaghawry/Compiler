//
// Created by marwan on 24/04/18.
//

#ifndef COMPILER_PARSETABLE_H
#define COMPILER_PARSETABLE_H


#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;


class ParseTable {

public:
    ParseTable (map<string, vector<pair<string, vector<pair<string, bool> > > > >firstMap,
                             map<string, vector<string>> followMap, vector<string> nonTermin, vector<string> termin);

     map<pair<string, string>, vector<pair<string, bool>> > getParseTable();
    map<pair<string, string>, vector<pair<string, bool>> > getParseTable_Ezzat();
     vector<string> getNonTerminals() ;
     vector<string> getTerminals() ;
     bool isTerminal (string s);
     vector<pair<string, bool> > getEpsilonRule();
     vector<pair<string, bool> > getSyncRule();
     vector<pair<string, bool> > getErrorRule();
    bool  isValidParseTable ();
     private:
    const string e ="\\L";
    map<string, vector<pair<string, vector<pair<string, bool> > > > > first;
    map <string ,vector <string>> follow;
    vector <string> nonTerminals;
    vector<string> terminals;
    vector<pair<string, bool> > epsilonRule;
    vector<pair<string, bool> > syncRule;
    vector<pair<string, bool> > errorRule;

};

//string , vector <pair<string first value terminal , vector<pair,bool>>
//    non
//true terminal
//false non
//First_Follow(map<//nonterminal string, //ORvector<vector<pair<string, bool>>>> grammer, vector<string> n_terminals, vector<stri#ng> terminals);


#endif //COMPILER_PARSETABLE_H


