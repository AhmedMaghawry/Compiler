#include "../headers/Generator.h"
#define ENDL -1

struct lexema {
	string type;
	string data;
};
stack<pair<string, int> > acceptance, printable;
vector<pair<Node, int[256]>> dfa;
int cur_Node = 0, partial_start_char, cur_char = 0;
string s_cur;			//current token
//vector<pair<lexema, int>> printable;

void parse(char c) {
	//s_cur += c;
	Writer w;
	string s = dfa[cur_Node].first.getAcceptance().second;
	//end of token
	if (c == ENDL) {
		if (!s.compare("no")) {
			//TOdo  recover('e',-1);
			cout << "error" << endl;
		} else {
			printable.push(make_pair(string(s), cur_char));
			cout<< s_cur.substr(partial_start_char,
				cur_char - partial_start_char) << endl;	 			//to be test
			//w.writeLinesToFile("output.txt", printable);
		}
		//printable.clear();
		//acceptance.clear();
		//cur_Node = 0;
	} else {
		cur_char++;
		if (s.compare("no")) {
			pair<string, int> p = make_pair(s, cur_char);
			acceptance.push(p);
		}
		int new_t = dfa[cur_Node].second[c];
		if (!dfa[new_t].first.name.compare("fi")) {
			//token didn't finish
			//TODO  recover(-2)
		} else {
			cur_Node = new_t;
		}

	}

}
void recover(char c, int loc) {

	switch (loc) {
	case 0:
		if (c == ' ' || c == '\n' || c == '\r') {
			//TODO handle many spaces and token to set symbol table
			//prepare stacks
			//printable.clear();
			//acceptance.clear();
			//cur_Node = 1;
			parse(ENDL);

			//
		} else
		s_cur += c;
		parse(c);
		cur_char = s_cur.size();		//for confirming only
		break;
	case -1:
		if (!acceptance.empty()) {
			recover('m', '-2');
			parse(ENDL);
		} else {
			//TODO error
		}
		break;
	case -2:							// -2 case could be intersected
		if (!acceptance.empty()) {
			pair<string, int> p = acceptance.pop();
			cur_char = p.second;
			while (!printable.empty() && printable.top().second > p.second)
				printable.pop();
			printable.push(p);
			while (cur_char < s_cur.length())
				parse(s_cur[cur_char]);
		}else {
			//TODO error
		}
		break;
	default:
		break;
	}

}
void scanne() {

	Reader R1;
	R1.readFiletoLines("code.txt");
	vector<string> inpute = R1.readingLines;
	for (int var = 0; var < inpute.size(); ++var) {
		for (char c : inpute[var]) {
			recover(c, 0);
			parse(c);
		}
	}

}

void Generator::run() {

	Reader R1;
	R1.readFiletoLines("code.txt");
	//
	vector<string> inpute = R1.readingLines;

}
