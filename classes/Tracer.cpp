//
// Created by marwan on 26/04/18.
//

#include "../headers/Tracer.h"
#include "../headers/Reader2.h"

Tracer::Tracer(vector<pair<string, string>> symbolTable,
               map<pair<string, string>, vector<pair<string, bool>>> parseTable,string startNode) {
    symbol_table=symbolTable;
    parse_table=parseTable;
    epsilonRule.push_back(make_pair("\\L",true));
    start_Node = startNode;
    IntailizeInput();
    IntailizeTraceStack();
}

 map<pair<string, string>, vector<pair<string, bool>>> Tracer::getParseTable()  {
    return parse_table;
}

void Tracer::setParseTable(const map<pair<string, string>, vector<pair<string, bool>>> &parseTable) {
    Tracer::parse_table = parseTable;
}

 vector<string> Tracer::getInput()  {
    return input;
}

void Tracer::setInput( vector<string> &input) {
    Tracer::input = input;
}
void Tracer:: IntailizeInput(){
    for(int i = 0; i < symbol_table.size(); i++) {

        if(symbol_table[i].first == "pun" || symbol_table[i].first == "assign") {
            input.push_back(symbol_table[i].second);
            input_ezzat.push(symbol_table[i].second);
        } else {
            if(symbol_table[i].first == "addop") {
                input.push_back(symbol_table[i].second);
                input_ezzat.push(symbol_table[i].second);
            }
            input.push_back(symbol_table[i].first);
            input_ezzat.push(symbol_table[i].first);
        }
    }
    input.push_back("$");
    input_ezzat.push("$");
}

stack <pair<string, bool>> Tracer::getTraceStack()  {
    return traceStack;
}
void Tracer:: IntailizeTraceStack(){
    traceStack.push (make_pair("$",true)); //terminal
    traceStack.push(make_pair(start_Node,false)); //non terminal
}

 string Tracer::getStart_Node()  {
    return start_Node;
}

void  Tracer:: evaluateTracingOutput() {
    pair <string,bool> stackTop;
    vector<pair<string, bool>> rule;
    int i=0;
    while(i<input.size() || !traceStack.empty()){
        stackTop=traceStack.top();
        if(stackTop.first ==input[i]){
            traceStack.pop();
            i++;
        }else{
            if(stackTop.second==true){
                //error terminals mismatch
                tracingOutput.push_back(make_pair("Error: missing "+stackTop.first+", inserted","errors"));
                traceStack.pop();
            }
            else{
                rule = parse_table[make_pair(stackTop.first,input[i])];
                if(rule[0].first=="error"){
                    //error there is no a valid rule
                    tracingOutput.push_back(make_pair("Error:(illegal "+stackTop.first+") – discard "+input[i],"errors"));
                    i++;
                }
                else {
                    // There is a valid rule then nonterminal and terminal is added to output
                    if(rule ==epsilonRule)
                        traceStack.pop();
                    else {
                        for(int j=0;j<rule.size();j++){
                            traceStack.push(rule[rule.size()-j-1]);
                            tracingOutput.push_back(make_pair(stackTop.first,input[i]));
                        }
                    }

                }
            }
        }
    }
    if(traceStack.empty()&&i==input.size()){
        tracingOutput.push_back(make_pair("Accept input!","accept"));
    } else{
        tracingOutput.push_back(make_pair("Error: input mismatch!","errors"));
    }
    writeOutputFile();
}

void  Tracer:: evaluateTracingOutput_Ezzat() {
    pair <string,bool> stackTop;
    vector<pair<string, bool>> rule;
    while(!input_ezzat.empty() || !traceStack.empty()){
        stackTop=traceStack.top();
        if (stackTop.second) {
            //It is a Terminal
            if(stackTop.first == input_ezzat.front()){
                traceStack.pop();
                input_ezzat.pop();
            }else{
                //error terminals mismatch
                tracingOutput.push_back(make_pair("Error: missing "+stackTop.first+", inserted","errors"));
                traceStack.pop();
            }
        } else {
            //It is N Terminal
            if(!parse_table.count(make_pair(stackTop.first,input_ezzat.front()))){
                //error there is no a valid rule
                tracingOutput.push_back(make_pair("Error:(illegal "+stackTop.first+") – discard "+input_ezzat.front(),"errors"));
                input_ezzat.pop();
            } else {
                rule = parse_table[make_pair(stackTop.first,input_ezzat.front())];
                traceStack.pop();
                // There is a valid rule then nonterminal and terminal is added to output
                if(rule != epsilonRule && rule[0].first != "sync") {
                    for(int j=0;j<rule.size();j++){
                        traceStack.push(rule[rule.size()-j-1]);
                    }
                    tracingOutput.push_back(make_pair(stackTop.first,input_ezzat.front()));
                } else if(rule == epsilonRule){
                    tracingOutput.push_back(make_pair(stackTop.first,input_ezzat.front()));
                }
            }
        }
    }
    /*if(traceStack.empty()&&i==input.size()){
        tracingOutput.push_back(make_pair("Accept input!","accept"));
    } else{
        tracingOutput.push_back(make_pair("Error: input mismatch!","errors"));
    }*/
    writeOutputFile();
}


 vector<pair<string, string>> Tracer::getTracingOutput()  {
    return tracingOutput;
}

void Tracer::writeOutputFile(){
    vector <string> output;
    vector<pair<string, bool>> rule;
    string str="";
    for(int i=0;i<tracingOutput.size();i++){
        if(tracingOutput[i].second=="errors"||tracingOutput[i].second=="accept")
            output.push_back(tracingOutput[i].first);
        else{
            rule = parse_table[make_pair(tracingOutput[i].first,tracingOutput[i].second)];
            str.append(tracingOutput[i].first+" -----> ");
            for(int j=0;j<rule.size();j++){
                str.append(rule[j].first);
                str.append(" , ");
            }
            output.push_back(str);
            str="";
        }
    }
    Writer writ;
    writ.writeLinesToFile("tracingOutputFile.txt",output);
}

void Tracer:: writeLeftDerivationFile() {
    vector<pair<string, bool>> rule1;
    vector<pair<string, bool>> startRule;
    vector<vector<pair<string, bool>>> totalRules;
    vector<vector<pair<string, bool>>> derivedTotalRules;
    Writer writ ;
    vector <string> deriveSteps;
    string ss="";
    int i , k=0,j,m=0;
    for ( i = 0; i < tracingOutput.size(); i++) {
        if (tracingOutput[i].second == "errors" ){
            writ.writeStringToFile("derivationFile.txt","");
            return;
        }
        else if ( tracingOutput[i].second == "accept")
            break;
        else{
            totalRules.push_back(parse_table[make_pair(tracingOutput[i].first,tracingOutput[i].second)]);
        }
    }

    //first step in derivation
    j=1;
    startRule=totalRules[0];
    derivedTotalRules.push_back(totalRules[0]);
    while(!isAllTerminals(startRule)){
        for(int i=0;i<startRule.size();i++){
            if(startRule[i].second==true){
                rule1.push_back(startRule[i]);
            }
            else {
                if(j < totalRules.size()) {
                    for(k=0;k<totalRules[j].size();k++){
                        if(totalRules[j][k].first=="\\L")
                            continue;
                        rule1.push_back(totalRules[j][k]);
                    }
                    for(m=i+1; m < startRule.size();m++){
                        rule1.push_back(startRule[m]);
                    }
                    derivedTotalRules.push_back(rule1);
                    startRule=rule1;
                    j++;
                    rule1.clear();
                    break;
                }
            }

        }
    }
    for(int i=0;i<derivedTotalRules.size();i++){
        for(int j=0;j<derivedTotalRules[i].size();j++){
            ss.append(derivedTotalRules[i][j].first+"  ");
        }
        deriveSteps.push_back(ss);
        ss="";
    }
    writ.writeLinesToFile("derivationFile.txt",deriveSteps);
}

bool Tracer:: isAllTerminals (vector<pair<string, bool>> rule){
   for(int j=0;j<rule.size();j++){
           if(rule[j].second == false)
               return false;
   }

    return true;
}