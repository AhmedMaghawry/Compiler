//
// Created by default on 20/03/18.
//

#ifndef COMPILER_GENERATOR_H
#define COMPILER_GENERATOR_H
#include "../headers/DFA.h"
#include "../headers/Reader2.h"

#define ENDL -1
#define START_NODE 1

vector<pair<Node, int[256]>> dfa;


int cur_Node = START_NODE, cur_line;

vector<pair<string, string>> symbol_table;
vector<string> output;

pair<string, string> last_accept;

bool bo_last_accept = false, first_recover = false, multi_recover = false;

string s_cur, s2_cur;			//current token

void lexal_analizer_run();
void intialize_scan();
void add_error();
void max_l_test(char c);
void max_l(char c);
void parse(char c, int mode);
void scan();
void write_outputs();

#endif //COMPILER_GENERATOR_H