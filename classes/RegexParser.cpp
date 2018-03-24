/*
 * RegexParser.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: saed
 */

#include "../headers/RegexParser.h"

void regular_definitions(string name, string def);
void regular_expressions(string name, string exp);
void Keyword(string line);
void Punctuation(string line);

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

void RegexParser::parse_rules() {

	Reader R1;
	R1.readFiletoLines("input.txt");
	vector<string> inpute = R1.readingLines;
	for (int i = 0; i < inpute.size(); i++) {
		inpute[i].erase(std::remove(inpute[i].begin(), inpute[i].end(), '\\'),
						inpute[i].end());

		switch (inpute[i][0]) {
			case '[':
				Punctuation(inpute[i]);
				break;
			case '{':
				Keyword(inpute[i]);
				break;
			default:
				string s = inpute[i];
				for (int j = 0; j < inpute[i].size(); ++j) {
					char c = inpute[i][j];
					if (c == '=') {
						string name = inpute[i].substr(0, j );
						string def = inpute[i].substr(j + 1, inpute[i].size() - 2);
						regular_definitions(name, def);
						break;
					}
					if (c == ':') {
						string name = inpute[i].substr(0, j);
						string exp = inpute[i].substr(j + 1, inpute[i].size() - 2);
						regular_expressions(name, exp);

						break;
					}
				}
//			for (char c : s) {
//				if (c == '=') {
//					regular_definitions(inpute[i]);
//					break;
//				}
//				if (c == ':') {
//					regular_expressions(inpute[i]);
//					break;
//				}
//			}

				break;
		}

	}

}

string preprocessing(string exp) {
	exp = ReplaceAll(exp, std::string("*"), std::string(" * "));
	exp = ReplaceAll(exp, std::string("+"), std::string(" + "));
	exp = ReplaceAll(exp, std::string("-"), std::string(" - "));
	exp = ReplaceAll(exp, std::string("|"), std::string(" | "));
	exp = ReplaceAll(exp, std::string(")"), std::string(" ) "));
	exp = ReplaceAll(exp, std::string("("), std::string(" ( "));
	return exp;
}

vector<string> get_strings(string line) {

	vector<string> words;
	istringstream iss(line);
	string token;
	while (std::getline(iss, token, ' ')) {

		if (token.size()&&token.compare("\r")) {
			words.push_back(token);
			cout << token << std::endl;
		}
	}
	cout << words.size()<<endl;
	return words;
}

void regular_definitions(string name, string def) {

	def = preprocessing(def);
	cout << name + "=" + def + "	RD" << endl;
	vector<string> words = get_strings(def);

}
void regular_expressions(string name, string exp) {

	exp = preprocessing(exp);
	cout << name + ":" + exp + "	Re" << endl;
	vector<string> words = get_strings(exp);
}

void Keyword(string line) {
	line = line.substr(1, line.size() - 3);
	cout << line + "	key" << endl;
	vector<string> words = get_strings(line);
	//keywords_to_nfa(words);

}
void Punctuation(string line) {

	line = line.substr(1, line.size() - 3);
	vector<string> words = get_strings(line);
	cout << line + "	pu" << endl;
	//punctuation_to_nfa(words);

}