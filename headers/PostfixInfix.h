//
// Created by arsanuos on 21/03/18.
//

#ifndef COMPILER_POSTFIXINFIX_H
#define COMPILER_POSTFIXINFIX_H

#include "NFA.h"
#include <string>
#include <map>
#include <stack>

class PostfixInfix {
private:
    map<string, NFA> def;
    map<pair<string, string>, vector<string>> map_of_transitions;
    string lastAssign;
    stack<NFA> nfas;
    vector<pair<string,NFA>> regular_exp;
    NFA eval(string operation, NFA a, NFA b);
    NFA eval_unary(string operation, NFA a);
    NFA calculate();
    NFA construct_regular_expression(vector<string> words, bool pun);
    NFA construct_definition(vector<string> words);
    NFA result;
    void handle_new_operation(string oper);
    void empty_all();
    string trim(string str);
    vector<string> symbol_table;
    stack<string> chars;
    stack<string> operations;
    vector<string> factorize(vector<string> words);
    void prepare_map_and_symbol_table();

public:
    void regular_definitions(string name, vector<string> words, bool pun);
    void regular_expressions(string name, vector<string> words, bool pun);
    void Keyword(vector<string> words, bool pun);
    void Punctuation(vector<string> words, bool pun);
    void collect();
    NFA  get_NFA();
    map<pair<string, string>, vector<string>> get_map();
    vector<string> get_symbol_table();

};


#endif //COMPILER_POSTFIXINFIX_H