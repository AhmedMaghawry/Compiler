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
string trim(string s) {
    int i;

    for (i = s.length()-1; i >= 0 && (s[i] == ' ' || s[i] == '\r'); i--)
        s[i] = 0;
    for (i = 0; i < s.length() && s[i] == ' '; i++)
        s[i] = 0;
    s.erase(std::remove(s.begin(), s.end(), 0),s.end());
    return s;
}

NFA RegexParser::parse_rules() {

    Reader R1;
    R1.readFiletoLines("input.txt");
    vector<string> inpute = R1.readingLines;
    for (int i = 0; i < inpute.size(); i++) {
        //inpute[i].erase(std::remove(inpute[i].begin(), inpute[i].end(), '\\'),
        //                inpute[i].end());
        inpute[i]=trim(inpute[i]);

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

vector<string> get_strings(string line) {

    vector<string> words;
    istringstream iss(line);
    string token;
    while (std::getline(iss, token, ' ')) {

        if (token.size() && token.compare("\r")) {
            words.push_back(token);
            cout << token << std::endl;
        }
    }
    cout << words.size() << endl;
    return words;
}

void RegexParser::regular_definitions(string name, string def) {

	def = preprocessing(def);
	cout << name + "=" + def + "	RD" << endl;
	vector<string> words = get_strings(def);
    p.regular_definitions(name, words, false);

}
void RegexParser::regular_expressions(string name, string exp) {

	exp = preprocessing(exp);
	cout << name + ":" + exp + "	Re" << endl;
	vector<string> words = get_strings(exp);
    p.regular_expressions(name, words, false);
}

void RegexParser::Keyword(string line) {
	line = line.substr(1, line.size() - 2);
	cout << line + "	key" << endl;
	vector<string> words = get_strings(line);
	p.Keyword(words, false);

}
void RegexParser::Punctuation(string line) {

	line = line.substr(1, line.size() - 2);
	vector<string> words = get_strings(line);
	cout << line + "	pu" << endl;
    p.Punctuation(words, true);

}

vector<string> RegexParser::get_symbol_table(){
    return p.get_symbol_table();
}

map<pair<string, string>, vector<string>> RegexParser::get_map(){
    return p.get_map();
}