//
// Created by default on 16/04/18.
//

#include <map>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <set>
#include "../headers/ModifiedDFA.h"

const string e ="\\L";
Node getNode(string name);
vector<string> sy;
map<string, vector<Node>> e_clous;
map<string, Node> nodesMap;
map<string, pair<int,string>> accFinal;
map<pair<string, string>, vector<string>> fullNodesMap;
map<pair<string, string>, string> finalTransMap;
map<string, string> trueMap;
map<string, vector<Node>> dfatr;
vector<Node> get_states (vector<Node> ns, string trans);
vector<Node> e_clo(Node n);
vector<Node> e_clo(vector<Node> ns);
vector<Node> get_states (Node n, string trans);

vector<Node> ModifiedDFA::getDfaGraph() {
    return convertMaptoGraph(sy);
}

/*
 * Use subset Construction Algorithm to convert
 * the graph from NFA to ModifiedDFA as a vector
 * of Nodes which contain the transition
 */
void ModifiedDFA::convert_from_NFA_to_DFA(vector<Node> graph, vector<string> symbs) {
    int s1 = symbs.size();
    sy = symbs;
    if (s1 == 0)
        return;

    for(int i = 0; i < graph.size(); i++) {
        nodesMap.insert(make_pair(graph[i].getNumber(), graph[i]));
    }

    for(int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].getTransitions().size(); ++j) {
            pair<string, string> p = make_pair(graph[i].getNumber(), graph[i].getTransitions()[j].getTransition());
            if (!fullNodesMap.count(p)) {
                vector<string> r;
                r.push_back(graph[i].getTransitions()[j].getTo());
                fullNodesMap.insert(make_pair(p, r));
            } else {
                vector<string> r = fullNodesMap[p];
                r.push_back(graph[i].getTransitions()[j].getTo());
                fullNodesMap[p] = r;
            }
        }
    }

    int counter = 0;
    //Remove E Clousre
    queue<vector<Node>> q;
    q.push(e_clo(graph[0]));
    while(!q.empty()) {
        vector<Node> curr = q.front();
        q.pop();
        if(isExsi(curr, dfatr))
            continue;

        dfatr.insert(make_pair(getName(curr), curr));

        for (int i = 0; i < symbs.size(); ++i) {
            vector<Node> u = e_clo(get_states(curr, symbs[i]));
            q.push(u);
            if(!trueMap.count(getName(curr))) {
                trueMap.insert(make_pair(getName(curr), to_string(counter)));
                counter++;
            }
            if(!trueMap.count(getName(u))) {
                trueMap.insert(make_pair(getName(u), to_string(counter)));
                counter++;
            }
            finalTransMap.insert(make_pair(make_pair(trueMap[getName(curr)],symbs[i]), trueMap[getName(u)]));
            accFinal.insert(make_pair(trueMap[getName(curr)],getAcc(curr)));
        }
    }
    //display_map(symbs);
}

bool ModifiedDFA::isExsist_in_list(Node node, vector<Node> final_gra) {
    for(Node n : final_gra) {
        if(n.getNumber() == node.getNumber())
            return true;
    }
    return false;
}

ModifiedDFA::ModifiedDFA() {}

void ModifiedDFA::display_map(vector<string> symbs) {

    cout << setw(17);
    for (int i = 0; i < symbs.size(); ++i) {
        cout << symbs[i] << setw(5);
    }
    cout << endl;

    map<string, vector<Node>>::iterator it;
    for (it = dfatr.begin(); it != dfatr.end(); it++)
    {
        cout << trueMap[it->first] << "::" << setw(10);
        for (int i = 0; i < symbs.size(); ++i) {
            int size = finalTransMap[make_pair(trueMap[it->first],symbs[i])].size();
            cout << finalTransMap[make_pair(trueMap[it->first],symbs[i])] << setw(5);
            if (size == 0)
                cout<<"--";
        }
        cout << "\t" << accFinal[trueMap[it->first]].second;
        cout << endl;
    }
}

vector<Node> ModifiedDFA::convertMaptoGraph(vector<string> symbs) {
    vector<Node> res;
    map<string, vector<Node>>::iterator it;
    for (it = dfatr.begin(); it != dfatr.end(); it++)
    {
        Node n(trueMap[it->first]);
        for (int i = 0; i < symbs.size(); ++i) {
            Transition t(finalTransMap[make_pair(trueMap[it->first],symbs[i])], symbs[i]);
            n.addTransitions(t);
        }
        n.addAcceptance(accFinal[trueMap[it->first]]);
        res.push_back(n);
    }
    return res;
}

bool ModifiedDFA::isExsi(vector<Node> list, map<string, vector<Node>> all) {
    return all.count(getName(list));
}

string ModifiedDFA::getName(vector<Node> list) {
    string res = "";
    for (int i = 0; i < list.size(); ++i) {
        res += list[i].getNumber();
    }
    sort(res.begin(), res.end());
    return res;
}

pair<int, string> ModifiedDFA::getAcc(vector<Node> vector) {
    pair<int, string> max(-1, "no");
    for (int i = 0; i < vector.size(); ++i) {
        if (max.first != -1) {
            if(vector[i].getAcceptance().first != -1 && vector[i].getAcceptance().first < max.first) {
                max = vector[i].getAcceptance();
            }
        }else {
            if(vector[i].getAcceptance().first != -1)
                max = vector[i].getAcceptance();
        }
    }
    return max;
}


vector<Node> e_clo(Node n) {
    if(e_clous.count(n.getNumber()) != 0)
        return e_clous[n.getNumber()];

    vector<Node> e_states;
    queue<Node> qu;

    qu.push(n);

    while (!qu.empty()) {
        Node curr = qu.front();
        e_states.push_back(curr);
        vector<Node> e_moves = get_states(curr, e);
        for(int i = 0; i < e_moves.size(); i++){
            if(!ModifiedDFA::isExsist_in_list(e_moves[i], e_states)) {
                qu.push(e_moves[i]);
            }
        }
        qu.pop();
    }
    e_clous[n.getNumber()] = e_states;
    return e_states;
}

vector<Node> e_clo(vector<Node> ns) {
    string name = "";
    for (int i = 0; i < ns.size(); ++i) {
        name += ns[i].getNumber();
    }
    sort(name.begin(), name.end());
    if(e_clous.count(name) != 0)
        return e_clous[name];
    vector<Node> e_states;
    for (int i = 0; i < ns.size(); i++) {
        vector<Node> curr = e_clo(ns[i]);
        e_states.reserve(e_states.size() + curr.size());
        e_states.insert(e_states.end(), curr.begin(), curr.end());
    }
    e_clous[name] = e_states;
    return e_states;
}

vector<Node> get_states (Node n, string trans) {
    vector<Node> res;
    for (int i = 0; i < fullNodesMap[make_pair(n.getNumber(), trans)].size(); i++) {
        res.push_back(getNode(fullNodesMap[make_pair(n.getNumber(), trans)][i]));
    }
    return res;
}

vector<Node> get_states (vector<Node> ns, string trans) {
    vector<Node> res;
    for (int i = 0; i < ns.size(); ++i) {
        vector<Node> stats = get_states(ns[i], trans);
        res.reserve(res.size() + stats.size());
        res.insert(res.end(), stats.begin(), stats.end());
    }
    return res;
}

Node getNode(string name) {
    return nodesMap.at(name);
}