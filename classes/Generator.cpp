#include "../headers/Generator.h"
#include "../headers/DFA.h"


//void parse(char c, int mode);

void Generator::intialize_scan() {
    s2_cur = s_cur = "";
    bo_last_accept = false;
   // cur_Node = START_NODE-1;
    cur = start;
}

void Generator::add_error() {

    string ms = "line ";
    ms += (cur_line + 48);
    ms += ":  error  ";
    //cout<<ms+s2_cur;
    pair<string, string> err_mes = make_pair(ms, s2_cur);
    symbol_table.push_back(err_mes);
    output.push_back(ms + s2_cur);
    intialize_scan();

}
//void Generator::max_l_test(char c) {
////	//	Writer w;
//    string state2 = "no";
//    string state = "id";		//  dfa[cur_Node].first.getAcceptance().second;
//    string s1 = s_cur;
//    string s2 = "000000000000000000000";
//    s2 = s2_cur;
//    vector<pair<string, string>> symbol_table2 = symbol_table;
//    //cout<<symbol_table;
//
////
//    if (c == ENDL || s2[6] == 'f' || s2[2] == 'd' || s2[2] == 'f') {//end of token
//        if (!state2.compare("no")) {			//test 2
//
//            if (bo_last_accept) {
//                pair<string, string> ll = last_accept;
//                symbol_table.push_back(last_accept);
//                output.push_back(last_accept.first);
//                string s_cur_ = s_cur.substr(last_accept.second.length());
//                intialize_scan();
//                s_cur = s_cur_;
//                parse(' ', 1);
//            } else
//                add_error();
//
//            cout << "tooken not accepted" << endl;
//        } else {
//
//            symbol_table.push_back(make_pair(state, s2_cur));
//            output.push_back(state);
//            intialize_scan();
//        }
//    } else {			//
//        int new_t;			//= dfa[cur_Node].second[c];
//        if (state.compare("no")) {
//            if (s2_cur.size()
//                && !(s2[2] == 'b' || s2[2] == 'd' || s2[2] == 'f')) {//test
//                last_accept = make_pair(state, s2_cur);
//                bo_last_accept = true;
//            }
//        }
//
//        if (0 && !dfa[new_t].first.getNumber().compare("fi")) {
//
//            if (bo_last_accept) {
//
//                symbol_table.push_back(last_accept);
//                output.push_back(last_accept.first);
//                string s_cur_ = s_cur.substr(last_accept.second.length());
//                intialize_scan();
//                s_cur = s_cur_;
//                parse(' ', 2);
//                return;
//            } else
//                add_error();
//        } else {
//            cur_Node = new_t;
//            s2_cur += c;
//        }
//    }
//
//}
//
//void Generator::max_l(char c) {
//
//    string state = dfa[cur_Node].first.getAcceptance().second;
//    if (c == ENDL) {			//end of token
//        if (!state.compare("no")) {			//test 2
//
//            if (bo_last_accept) {
//                pair<string, string> ll = last_accept;
//                symbol_table.push_back(last_accept);
//                output.push_back(last_accept.first);
//                string s_cur_ = s_cur.substr(last_accept.second.length());
//                intialize_scan();
//                s_cur = s_cur_;
//                parse(' ', 1);
//            } else
//                add_error();
//
//            //cout << "tooken not accepted" << endl;
//        } else {
//
//            symbol_table.push_back(make_pair(state, s2_cur));
//            output.push_back(state);
//            intialize_scan();
//        }
//    } else {			//
//        int new_t= dfa[cur_Node].second[c];
//        if (state.compare("no")) {
//            if (s2_cur.size()) {			//test
//                last_accept = make_pair(state, s2_cur);
//                bo_last_accept = true;
//            }
//        }
//        //TODO: Check name
//        if (new_t==-1) {            //fie check
//
//            if (bo_last_accept) {
//
//                symbol_table.push_back(last_accept);
//                output.push_back(last_accept.first);
//                string s_cur_ = s_cur.substr(last_accept.second.length());
//                intialize_scan();
//                s_cur = s_cur_;
//                parse(' ', 2);DFA::
//                return;
//            } else
//                add_error();
//        } else {
//            cur_Node = new_t-1;
//            s2_cur += c;
//        }
//    }
//
//}

void Generator::max_l(char c) {

    string state = cur.getAcceptance().second;
    if (c == ENDL) {			//end of token
        if (!state.compare("no")) {			//test 2

            if (bo_last_accept) {
                pair<string, string> ll = last_accept;
                symbol_table.push_back(last_accept);
                output.push_back(last_accept.first);
                string s_cur_ = s_cur.substr(last_accept.second.length());
                intialize_scan();
                s_cur = s_cur_;
                parse(' ', 1);
            } else
                add_error();

            //cout << "tooken not accepted" << endl;
        } else {

            symbol_table.push_back(make_pair(state, s2_cur));
            output.push_back(state);
            intialize_scan();
        }
    } else {			//
        string new_t = getTransitionNode(cur, c);
        if (state.compare("no")) {
            if (s2_cur.size()) {			//test
                last_accept = make_pair(state, s2_cur);
                bo_last_accept = true;
            }
        }
        //TODO: Check name
        if (!new_t.compare("-1")) {            //fie check

            if (bo_last_accept) {

                symbol_table.push_back(last_accept);
                output.push_back(last_accept.first);
                string s_cur_ = s_cur.substr(last_accept.second.length());
                intialize_scan();
                s_cur = s_cur_;
                parse(' ', 2);
                return;
            } else
                add_error();
        } else {
            cur = getNode(new_t,dfa);
            s2_cur += c;
        }
    }

}

void Generator::parse(char c, int mode) {

    switch (mode) {

        case 0:
            if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == ENDL) {
                if (s_cur.size())
                    max_l(ENDL);

            } else {
                s_cur += c;
                max_l(c);
            }
            break;
        case 1:				//recover after token fail
            parse(' ', 2);
            max_l(ENDL);
            break;
        case 2:				//recover catch FI in middle of token
            bool owner = false;
            if (!first_recover)
                owner = first_recover = true;
            for (int i = 0; i < s_cur.size() && !multi_recover; ++i) {
                max_l(s_cur[i]);
            }
            if (owner)
                owner = first_recover = multi_recover = false;
            else
                multi_recover = true;
            break;

    }

}

void Generator::scan() {

    Reader R1;
    R1.readFiletoLines("code.txt");
    vector<string> inpute = R1.readingLines;
    intialize_scan();
    for (cur_line = 0; cur_line < inpute.size(); ++cur_line) {
        for (char c : inpute[cur_line]) {
            parse(c, 0);
        }
        parse(ENDL, 0);
        intialize_scan();
    }

}

void Generator::write_outputs() {

    Writer w;
    w.writeLinesToFile("outpute.txt", output);

    vector<string> sym;
    for (int i = 0; i < symbol_table.size(); ++i) {
        string str = symbol_table[i].first;
        int j = str.size();
        while (j++ < 20)
            str += " ";
        str += "  |      " + symbol_table[i].second;
        sym.push_back(str);
    }
    w.writeLinesToFile("sympoltable.txt", sym);
}

void Generator::lexal_analizer_run() {
    scan();
    write_outputs();
}

string Generator::getTransitionNode(Node node, char c) {
    for(Transition t : node.getTransitions()) {
        if(t.getTransition()[0] == c){
            return t.getTo();
        }
    }
    return "-1";
}

Generator::Generator(const Node &cur, const vector<Node> &dfa, Node sta) : cur(cur), dfa(dfa),
                                                                                 start(sta) {}



//
//int main_() {
//    Generator::lexal_analizer_run();
//    return 0;
//}