/*
 * RegexParser.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: Saed
 */

#include "../headers/RegexParser.h"

vector<string> get_strings(string line, char sparator);
string preprocessing(string exp);

RegexParser::RegexParser() {
	// TODO Auto-generated constructor stub

}

RegexParser::~RegexParser() {
	// TODO Auto-generated destructor stub
}

std::string ReplaceAll(std::string str, const std::string& from,
		const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}
string trim(string s) {
	int i;

	for (i = s.length() - 1; i >= 0 && (s[i] == ' ' || s[i] == '\r'); i--)
		s[i] = 0;
	for (i = 0; i < s.length() && s[i] == ' '; i++)
		s[i] = 0;
	s.erase(std::remove(s.begin(), s.end(), 0), s.end());
	return s;
}
map<string, vector<vector<pair<string, bool> > > > RegexParser::parse_syn_rules() {
	vector<pair<string, vector<vector<pair<string, bool> > > > > all_rules;

	Reader R1;
	R1.readFiletoLines("input_syntax.txt");
	vector<string> inpute = R1.readingLines;

	//parse input syntax
	for (int i = 0; i < inpute.size(); i++) {
		pair<string, vector<vector<pair<string, bool> > > > current_rule;
		string str = trim(inpute[i]);
		while (i < inpute.size() - 1 && trim(inpute[i + 1])[0] != '#')
			str += trim(inpute[++i]);

		int j;
		for (j = 0; j < str.size() && str[j] != '='; ++j)
			;
		string name = trim(str.substr(1, j - 1));
		non_terminal.push_back(name);
		current_rule.first = name;
		string rule = trim(str.substr(j + 1));
		rule = ReplaceAll(rule, std::string("|"), std::string(" | "));
		vector<string> rules_list = get_strings(rule, '|');
		vector<vector<pair<string, bool> > > rules;
		for (j = 0; j < rules_list.size(); ++j) {
			vector<pair<string, bool> > words = get_pairs(rules_list[j]);
			rules.push_back(words);
		}
		current_rule.second = rules;
		all_rules.push_back(current_rule);
		rules_map[current_rule.first] = current_rule.second;

	}
	for (auto i : terminal_set) {
		terminal.push_back(i);
	}
//	for(set<string>::iterator it =terminal_set.begin();it!=terminal_set.end();it++){
//		terminal.push_back(*it);
//	}
	return rules_map;
}

vector<string> RegexParser::get_non_terminal_symbols() {
	return non_terminal;
}

void RegexParser::set_non_terminal_symbols(vector<string> new_non_terminals) {
	non_terminal = new_non_terminals;
}

vector<string> RegexParser::get_terminal_symbols() {
	return terminal;
}
map<string, vector<vector<pair<string, bool>>> > RegexParser::get_rules_map() {
	return rules_map;
}


vector<pair<string, bool> > RegexParser::get_pairs(string line) {

	vector<pair<string, bool> > words;
	istringstream iss(line);
	string token;
	while (std::getline(iss, token, ' ')) {
		if (token.size() && token.compare("\r")) {
			pair<string, bool> pr;
			if (token[0] == -30) {
				string str = token.substr(3, token.size() - 6);
				pr = make_pair(str, true);
				if (str.compare("\\L"))
					terminal_set.insert(str);
			} else if(token[0] == '\''){
				string str = token.substr(1, token.size() - 2);
				pr = make_pair(str, true);
				if (str.compare("\\L"))
					terminal_set.insert(str);
			} else {
				pr = make_pair(token, false);

			}
			words.push_back(pr);
		}
	}
	//cout << words.size() << endl;
	return words;
}


NFA RegexParser::parse_rules() {

	Reader R1;
	R1.readFiletoLines("input.txt");
	vector<string> inpute = R1.readingLines;
	for (int i = 0; i < inpute.size(); i++) {
		//inpute[i].erase(std::remove(inpute[i].begin(), inpute[i].end(), '\\'),
		//                inpute[i].end());
		inpute[i] = trim(inpute[i]);

		switch (inpute[i][0]) {
		case '[':
			Punctuation(inpute[i]);
			break;
		case '{':
			Keyword(inpute[i]);
			break;
		default:
			for (int j = 0; j < inpute[i].size(); ++j) {
				char c = inpute[i][j];
				if (c == '=') {
					string name = trim(inpute[i].substr(0, j));
					string def = trim(inpute[i].substr(j + 1));
					regular_definitions(name, def);
					break;
				}
				if (c == ':') {
					string name = trim(inpute[i].substr(0, j));
					string exp = trim(inpute[i].substr(j + 1));
					regular_expressions(name, exp);
					break;
				}
			}
			break;
		}

	}
	p.collect();
	return p.get_NFA();

}

string preprocessing(string exp) {
	exp = ReplaceAll(exp, std::string("\\"), std::string(" \\ "));
	exp = ReplaceAll(exp, std::string("*"), std::string(" * "));
	exp = ReplaceAll(exp, std::string("+"), std::string(" + "));
	exp = ReplaceAll(exp, std::string("-"), std::string(" - "));
	exp = ReplaceAll(exp, std::string("|"), std::string(" | "));
	exp = ReplaceAll(exp, std::string(")"), std::string(" ) "));
	exp = ReplaceAll(exp, std::string("("), std::string(" ( "));
	return exp;
}

vector<string> get_strings(string line, char sparator) {

	vector<string> words;
	istringstream iss(line);
	string token;
	while (std::getline(iss, token, sparator)) {

		if (token.size() && token.compare("\r")) {
			words.push_back(trim(token));
			//cout << token << std::endl;
		}
	}
	return words;
}

void RegexParser::regular_definitions(string name, string def) {

	def = preprocessing(def);
	//cout << name + "=" + def + "	RD" << endl;
	vector<string> words = get_strings(def, ' ');
	p.regular_definitions(name, words, false);

}
void RegexParser::regular_expressions(string name, string exp) {

	exp = preprocessing(exp);
	//cout << name + ":" + exp + "	Re" << endl;
	vector<string> words = get_strings(exp, ' ');
	p.regular_expressions(name, words, false);
}

void RegexParser::Keyword(string line) {
	line = line.substr(1, line.size() - 2);
	//cout << line + "	key" << endl;
	vector<string> words = get_strings(line, ' ');
	p.Keyword(words, false);

}
void RegexParser::Punctuation(string line) {

	line = line.substr(1, line.size() - 2);
	vector<string> words = get_strings(line, ' ');
	//cout << line + "	pu" << endl;
	p.Punctuation(words, true);

}

vector<string> RegexParser::get_symbol_table() {
	return p.get_symbol_table();
}

map<pair<string, string>, vector<string>> RegexParser::get_map() {
	return p.get_map();
}

