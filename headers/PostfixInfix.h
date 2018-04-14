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
    std::map<string, NFA> def;
    string lastAssign;
    std::stack<string> chars;
    std::stack<NFA> nfas;
    std::stack<string> operations;
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
    vector<string> factorize(vector<string> words);

public:
    void regular_definitions(string name, vector<string> words, bool pun);
    void regular_expressions(string name, vector<string> words, bool pun);
    void Keyword(vector<string> words, bool pun);
    void Punctuation(vector<string> words, bool pun);
    void collect();
    NFA  get_NFA();
    vector<string> get_symbol_table();

};


#endif //COMPILER_POSTFIXINFIX_H
