//
// Created by marwan on 26/04/18.
//

#ifndef COMPILER_TRACER_H
#define COMPILER_TRACER_H


#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

class Tracer {

public:
     Tracer(vector<pair<string, string>> symbolTable, map<pair<string, string>, vector<pair<string, bool>> >parseTable,string startNode);


     string getStart_Node() ;
     vector<string> getInput() ;
     map<pair<string, string>, vector<pair<string, bool>>> getParseTable() ;
     stack <pair<string, bool>> getTraceStack();
     vector<pair<string, string>> getTracingOutput() ;


    void setParseTable(const map<pair<string, string>, vector<pair<string, bool>>> &parse_table);
    void setInput( vector<string> &input);
    void IntailizeInput();
    void IntailizeTraceStack();
    void evaluateTracingOutput();
    void writeOutputFile();
    void writeLeftDerivationFile();
    bool isAllTerminals (vector<pair<string, bool>> rule);
    vector<pair<string, bool> > epsilonRule;
    void evaluateTracingOutput_Ezzat();


private:
    vector<pair<string, string>> symbol_table;
    map<pair<string, string>, vector<pair<string, bool>> > parse_table;
    vector<string> input;
    queue<string> input_ezzat;
    stack <pair<string, bool>> traceStack;
    string start_Node;
    vector<pair<string,string> > tracingOutput;


};


#endif //COMPILER_TRACER_H
