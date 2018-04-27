/*
 * RegexParser.h
 *
 *  Created on: Mar 18, 2018
 *      Author: saed
 */

#ifndef REGEXPARSER_H_
#define REGEXPARSER_H_

#include <bits/stdc++.h>
#include "Reader2.h"
#include "../headers/PostfixInfix.h"
#include "../headers/NFA.h"

using namespace std;

class RegexParser {
private:
	PostfixInfix p;
	vector<string> non_terminal, terminal;
	set<string> terminal_set;
	map<string, vector<vector<pair<string, bool> > > > rules_map;
	vector<pair<string, bool> > get_pairs(string line);

public:
	RegexParser();
	virtual ~RegexParser();
	map<string, vector<vector<pair<string, bool>>> > parse_syn_rules();
	map<string,vector<vector<pair < string, bool>>>> get_rules_map();
	vector<string>get_non_terminal_symbols();
	vector<string>get_terminal_symbols();
	NFA parse_rules();
	void regular_definitions(string name, string def);
	void regular_expressions(string name, string exp);
	void Keyword(string line);
	void Punctuation(string line);
	vector<string> get_symbol_table();
	map<pair<string, string>, vector<string>> get_map();
};

#endif /* REGEXPARSER_H_ */
