//
// Created by arsanuos on 21/03/18.
//

#define ccat "concat"
#define eps "\\L"

#include "../headers/PostfixInfix.h"
#include "../headers/Construction.h"
#include "../headers/OperationHandler.h"
#include "../headers/Evaluator.h"
#include <iostream>


void PostfixInfix::regular_definitions(string name, vector<string> words, bool pun) {
    empty_all();
    NFA definition = construct_regular_expression(words, pun);
    name = trim(name);
    def.insert(pair<string, NFA>(name, definition));
    empty_all();
    cout<<"-----------------------------------------------------"<<endl;
}
void PostfixInfix::regular_expressions(string name, vector<string> words, bool pun) {
    empty_all();
    NFA expression = construct_regular_expression(words, pun);
    name = trim(name);
    regular_exp.push_back(pair<string, NFA>(name, expression));
    empty_all();
    cout<<"------------------------------------------------------"<<endl;
}

void PostfixInfix::Keyword(vector<string> words, bool pun) {
    //words = factorize(words);
    for(int i = 0 ;i < words.size(); i++){
        vector<string> tmp;
        if(words[i].size() != 0){
            for(int j = 0 ;j < words[i].size(); j++){
                string con(1, words[i][j]);
                tmp.push_back(con);
            }
        }else{
            tmp.push_back(words[i]);
        }
        regular_expressions(words[0], tmp, pun);
    }

}
void PostfixInfix::Punctuation(vector<string> words, bool pun) {
    words = factorize(words);
    regular_expressions(words[0],words, pun);
}

void PostfixInfix::collect(){
    regular_exp[0].second.getEndNode().addAcceptance(pair<int, string>(regular_exp.size(),
                                                                       regular_exp[0].first));
    result = regular_exp[0].second;
    for(int i = 1 ;i < regular_exp.size(); i++){
        regular_exp[i].second.getEndNode().addAcceptance(pair<int, string>(i, regular_exp[i].first));
        result = Evaluator::oring(result, regular_exp[i].second);
    }
}

NFA PostfixInfix::get_NFA(){
    return result;
}




NFA PostfixInfix::eval(string operation, NFA a, NFA b){
    if(operation == ccat){
        return Evaluator::concat(a, b);
    }else if(operation == "|"){
        return Evaluator::oring(a, b);
    }else if(operation == "-"){
        return Evaluator::dash(a, b);
    }
    throw "non determined operation";
}

NFA PostfixInfix::eval_unary(string operation, NFA a){
    if(operation == "*"){
        return Evaluator::star(a);
    }else if(operation == "+"){
        return Evaluator::plus(a);
    }
    throw "non determined unary operation";
}


NFA PostfixInfix::calculate(){
    string operation = operations.top();
    operations.pop();
    string x1 = chars.top();chars.pop();
    NFA a = nfas.top();nfas.pop();
    NFA operation_result;
    if(OperationHandler::isUnary(operation)){
        operation_result = eval_unary(operation, a);
        string operation_string = x1 + " " +  operation;
        nfas.push(operation_result);
        chars.push(operation_string);
    }else{
        string x2 = chars.top();chars.pop();
        string operation_string = x2 + " " + operation + " " + x1;
        NFA b = nfas.top();nfas.pop();
        operation_result = eval(operation ,b ,a);
        nfas.push(operation_result);
        chars.push(operation_string);
    }
    cout<<chars.top()<<endl;
    return operation_result;
}



NFA PostfixInfix::construct_regular_expression(vector<string> words, bool pun) {
    bool last_is_char = false;
    bool last_is_closed_group = false;
    bool last_is_unary = false;
    for(int i = 0 ;i < words.size(); i++){
        map<string, NFA>::iterator tmp = def.find(words[i]);
        if(tmp != def.end()){
            //definition found
            chars.push(words[i]);
            nfas.push(tmp->second);
            if(last_is_char || last_is_closed_group || last_is_unary){
                while(operations.size() > 0 && operations.top() != "(" && operations.top() != ")"
                      && OperationHandler::precedence(ccat) <= OperationHandler::precedence(operations.top())){
                    calculate();
                }
                operations.push(ccat);
            }
            last_is_char = true;
            last_is_closed_group = false;
            last_is_unary = false;
        }else if(OperationHandler::isOperation(words[i]) && i > 0 && words[i -1] != "\\"){
            if(OperationHandler::isUnary(words[i])){
                operations.push(words[i]);
                calculate();
                last_is_unary = true;
            }else{
                while(operations.size() > 0 && operations.top() != "(" && operations.top() != ")"
                      && OperationHandler::precedence(words[i]) <= OperationHandler::precedence(operations.top())){
                    calculate();
                }
                operations.push(words[i]);
                last_is_unary = false;
            }
            last_is_closed_group = false;
            last_is_char = false;
        }else if(words[i] == ")" && !pun){
            string op = operations.top();
            while(op != "("){
                calculate();
                op = operations.top();
            }
            operations.pop();
            last_is_closed_group = true;
            last_is_char = false;
            last_is_unary = false;
        }else if(words[i] == "(" && !pun){
            if(last_is_char){
                operations.push(ccat);
            }
            operations.push(words[i]);
            last_is_closed_group = false;
            last_is_char = false;
            last_is_unary = false;
        }else if(words[i].size() == 1 && (words[i] != "\\" || (i > 0 && words[i] == "L" && words[i - 1] == "\\"))){
            if(i > 0 && words[i] == "L" && words[i - 1] == "\\"){
                words[i] = eps;
            }
            chars.push(words[i]);
            nfas.push(Construction::construct(words[i]));
            if(last_is_char || last_is_closed_group || last_is_unary){
                while(operations.size() > 0 && operations.top() != "(" && operations.top() != ")"
                      && OperationHandler::precedence(ccat) <= OperationHandler::precedence(operations.top())){
                    calculate();
                }
                operations.push(ccat);
            }
            last_is_char = true;
            last_is_unary = false;
        }else if(words[i].size() != 1){
            vector<string> fac;
            fac.push_back(words[i]);
            vector<string> tmp = factorize(fac);
            for(int k = 0 ;k < tmp.size(); k++){
                chars.push(tmp[k]);
                nfas.push(Construction::construct(tmp[k]));
                if(last_is_char || last_is_closed_group || last_is_unary){
                    while(operations.size() > 0 && operations.top() != "(" && operations.top() != ")"
                          && OperationHandler::precedence(ccat) <= OperationHandler::precedence(operations.top())){
                        calculate();
                    }
                    operations.push(ccat);
                }
                last_is_char = true;
                last_is_unary = false;
                last_is_closed_group = false;
            }

        }else if(words[i] != "\\") {
            throw "non-classified char";
        }
    }
    while(operations.size() != 0){
        calculate();
    }

    NFA result = nfas.top();
    nfas.pop();
    return result;
}


void PostfixInfix::empty_all(){
    while(nfas.size()){
        nfas.pop();
    }
    while(chars.size()){
        chars.pop();
    }
    while(operations.size()){
        operations.pop();
    }
}


string PostfixInfix::trim(string str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}


vector<string> PostfixInfix::get_symbol_table(){
    if(symbol_table.size() == 0){
        for(int i = 0 ;i < 256; i++){
            char x = i;
            string tmp(1, x);
            symbol_table.push_back(tmp);
        }
    }
    return symbol_table;
}

NFA PostfixInfix::construct_definition(vector<string> words){
    bool last_is_char = false;
    bool last_is_closed_group = false;
    for(int i = 0 ;i < words.size(); i++){
        if(words[i].size() == 1 && isalnum(words[i].at(0))){
            chars.push(words[i]);
            nfas.push(Construction::construct(words[i]));
            if(last_is_char || last_is_closed_group){
                while(operations.size() > 0 && operations.top() != "(" && operations.top() != ")"
                      && OperationHandler::precedence(ccat) <= OperationHandler::precedence(operations.top())){
                    calculate();
                }
                operations.push(ccat);
            }
            last_is_char = true;
        }else if(OperationHandler::isOperation(words[i])){
            if(OperationHandler::isUnary(words[i])){
                operations.push(words[i]);
                calculate();
            }else{
                while(operations.size() > 0 && operations.top() != "(" && operations.top() != ")"
                      && OperationHandler::precedence(words[i]) <= OperationHandler::precedence(operations.top())){
                    calculate();
                }
                operations.push(words[i]);
            }
            last_is_closed_group = false;
            last_is_char = false;
        }else if(words[i] == ")"){
            string op = operations.top();
            do{
                calculate();
                op = operations.top();
            }while(op != "(");
            operations.pop();
            last_is_closed_group = true;
        }else if(words[i] == "(" ){
            if(last_is_char){
                operations.push(ccat);
            }
            operations.push(words[i]);
            last_is_closed_group = false;
            last_is_char = false;
        }else {
            throw "non-classified char";
        }
    }
    while(operations.size() != 0){
        calculate();
    }

    NFA result = nfas.top();
    nfas.pop();
    return result;
}


vector<string> PostfixInfix::factorize(vector<string> words){
    vector<string> tmp;
    for(int i = 0 ;i < words.size(); i++){
        if(words[i].size() != 0){
            for(int j = 0 ;j < words[i].size(); j++){
                string con(1, words[i][j]);
                tmp.push_back(con);
            }
        }else{
            tmp.push_back(words[i]);
        }

    }
    return tmp;
}