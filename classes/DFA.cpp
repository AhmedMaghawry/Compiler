//
// Created by default on 19/03/18.
//

#include <iostream>
#include <bits/stdc++.h>
#include "../headers/DFA.h"
#include "../headers/Evaluator.h"

const string e ="\\L";
Node fi("");
vector<string> trans_symb;
vector<Node> nfaGraph;
vector<Node> nfa_without_e;
bool visited[1000];
bool visited_min[1000];

vector<Node> remove_e_clousre(vector<Node> graph);
string getName_of(vector<Node> noo);
void display_graph(vector<Node> nodes);
bool isAcceptance(Node node);
void e_clousre(vector<Node> &nodes, Node &node);

void remove_duplicates(vector<Node> &nodes);

void add_new_transitions(Node &node, vector<Node> vector);

Node getNode(string basic_string, vector<Node> list);

string getName_of_e(vector<Node> vector);

vector<Node> DFA::getDfaGraph() {
    return dfaGraph;
}

void DFA::setDfaGraph(vector<Node> dfa) {
    dfaGraph = dfa;
}

/*
 * Use subset Construction Algorithm to convert
 * the graph from NFA to DFA as a vector
 * of Nodes which contain the transition
 */
void DFA::convert_from_NFA_to_DFA(vector<Node> graph, vector<string> symbs) {
    nfaGraph = graph;
    int s = symbs.size();
    if (s == 0)
        return;
    for(int i = 0; i < s; i++){
        trans_symb.push_back(symbs[i]);
    }
    /*Start Remove E Clousre from NFA*/
    vector<Node> nfaGraph_without_clouser = remove_e_clousre(graph);
    nfa_without_e = nfaGraph_without_clouser;
    cout << "--------------------- NFA without E"<<endl;
    display_graph(nfaGraph_without_clouser);
    /*End Remove Now we have NFA without E clousre*/
    //Tested Till Here
    vector<Node> dfaGraph_final;
    run_dfa(dfaGraph_final, nfaGraph_without_clouser);
    removeRedundant(dfaGraph_final);
    setDfaGraph(dfaGraph_final);
    cout << "--------------------- Final DFA"<<endl;
    //display_graph(getDfaGraph());
}

void DFA::run_dfa(vector<Node> &final_graph, vector<Node> nfa_without_clousre) {
    Node start_node = nfa_without_clousre[0];
    queue<Node> q;
    q.push(start_node);
    //BFS search
    while (!q.empty()) {
        Node n = q.front();
        q.pop();
        for(string symb : trans_symb) {
            string name_of_new_node = "";
            vector<Node> nodes_to_go;
            for (Transition t : n.getTransitions()) {
                if(t.getTransition() == symb) {
                    name_of_new_node.append(t.getTo());
                    nodes_to_go.push_back(getNode(t.getTo(), nfa_without_clousre));
                }
            }
            if(name_of_new_node != fi.getNumber()) {
                Node new_node = create_new_node(sort_name(name_of_new_node), nodes_to_go);
                //new_node.addAcceptance(getNode().getAcceptance());
                add_new_transitions(new_node, nodes_to_go);
                n.emptyTransitions(symb);
                Transition newT(sort_name(name_of_new_node), symb);
                n.addTransitions(newT);
                if (!isExsist(new_node, q) && new_node.getNumber() != n.getNumber() && !isExsist_in_list(new_node, final_graph)) {
                    q.push(new_node);
                }
            } else {
                Transition newT(fi.getNumber(), symb);
                n.addTransitions(newT);
            }
        }
        final_graph.push_back(n);
    }
}

Node DFA::create_new_node(string name, vector<Node> nodes) {
    Node res(name);
    add_temp_trans(res, nodes);
    return res;
}

void DFA::add_temp_trans(Node &node, vector<Node> nodes_to_take_its_trans) {
    for (Node n : nodes_to_take_its_trans) {
        for (Transition t : n.getTransitions()) {
            node.addTransitions(t);
            node.addAcceptance(getNode(t.getTo(), nfa_without_e).getAcceptance());
        }
    }
}

bool DFA::isExsist(Node node, queue<Node> list) {
    queue<Node> tmp_q = list; //copy the original queue to the temporary queue
    while (!tmp_q.empty())
    {
        Node q_element = tmp_q.front();
        if(q_element.getNumber() == node.getNumber())
            return true;
        tmp_q.pop();
    }
    return false;
}

void DFA::removeRedundant(vector<Node> &list) {
    remove_duplicates(list);
}

string DFA::sort_name(string basic_string) {
    sort(basic_string.begin(), basic_string.end());
    return basic_string;
}

bool DFA::isExsist_in_list(Node node, vector<Node> final_gra) {
    for(Node n : final_gra) {
        if(n.getNumber() == node.getNumber())
            return true;
    }
    return false;
}

/*
 * Remove the E clousre which take the NFA graph
 * and return NFA but without E clousre
 */
vector<Node> remove_e_clousre(vector<Node> graph) {
    int size = graph.size();
    vector<Node> res;
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < size; ++i) {
        Node n(graph[i].getNumber());
        if (!visited[Evaluator::convert(graph[i].getNumber())]) {
            vector<Transition> trans = graph[i].getTransitions();
            vector<Node> nodes_by_ebs;
            Node temp = graph[i];
            e_clousre(nodes_by_ebs, temp);
            for(Node nn : nodes_by_ebs) {
                temp.addAcceptance(nn.getAcceptance());
            }
            nodes_by_ebs.push_back(temp);
            remove_duplicates(nodes_by_ebs);
            //Node n(getName_of(nodes_by_ebs));
            add_new_transitions(n, nodes_by_ebs);
            res.push_back(n);
        }
    }
        //}
        return res;
    }

/*string getName_of(vector<Node> noo) {
    string res = "";
    for(Node n : noo) {
        res.append(n.getNumber());
    }
    return res;
}*/

void add_new_transitions(Node &node, vector<Node> nodes) {
    for (string symb : trans_symb) {
        for (Node n : nodes) {
            for (Transition t : n.getTransitions()) {
                if(t.getTransition() == symb) {
                    vector<Node> nodes_in_final;
                    Node node_intermediate = getNode(t.getTo(), nfaGraph);
                    nodes_in_final.push_back(node_intermediate);
                    /*memset(visited, false, sizeof(visited));
                    e_clousre(nodes_in_final, node_intermediate);*/
                    remove_duplicates(nodes_in_final);
                    for (Node final_node : nodes_in_final) {
                        Transition tran(final_node.getNumber() ,symb);
                        node.addTransitions(tran);
                        node.addAcceptance(n.getAcceptance());
                    }
                }
            }
            node.addAcceptance(n.getAcceptance());
        }
    }
}

void remove_duplicates(vector<Node> &nodes){
    for (int i = 0; i < nodes.size(); ++i) {
        for (int j = i + 1; j < nodes.size(); ++j) {
            if(nodes[i].getNumber() == nodes[j].getNumber()) {
                nodes.erase(nodes.begin()+j);
            }
        }
    }
}

/*void e_clousre(vector<Node> &nodes, Node &node) {
    //DFS
    for (Transition transition : node.getTransitions()) {
        if(transition.getTransition() == e) {
            int index = Evaluator::convert(transition.getTo());
            if(!visited[index]) {
                Node to_go_node = getNode(transition.getTo(), nfaGraph);
                visited[index] = true;
                e_clousre(nodes, to_go_node);
                node.addAcceptance(to_go_node.getAcceptance());
                nodes.push_back(to_go_node);
            }
        }
    }
}*/

    bool isSelfi(vector<Node> nodes, string to_go) {
        for(Node n : nodes) {
            if(n.getNumber() == to_go)
                return true;
        }
        return false;
    }

void e_clousre(vector<Node> &nodes, Node &node) {
    //DFS
    for (Transition transition : node.getTransitions()) {
        if(transition.getTransition() == e && !isSelfi(nodes, transition.getTo())) {
                Node to_go_node = getNode(transition.getTo(), nfaGraph);
            int index = Evaluator::convert(transition.getTo());
            visited[index] = true;
            node.addAcceptance(to_go_node.getAcceptance());
                e_clousre(nodes, to_go_node);
                node.addAcceptance(to_go_node.getAcceptance());
                nodes.push_back(to_go_node);
            }
    }
}

Node getNode(string node_name, vector<Node> list) {
    for(Node i : list) {
        if(i.getNumber() == node_name)
            return i;
    }
}

void display_graph(vector<Node> nodes) {
    for (Node node : nodes) {
        for (Transition t : node.getTransitions()) {
            cout << node.getNumber() << "-- " << t.getTransition() << " --> " << t.getTo() << isAcceptance(node) << endl;
        }
    }
}

bool isAcceptance(Node node) {
    if (node.getAcceptance().first == -1)
        return false;
    return true;
}

bool compar (Node n1, Node n2) {
    return (stoi(n1.getNumber()) < stoi(n2.getNumber()));
}

vector<pair<Node, vector<int>>> DFA::get_saeed_array(vector<Node> nodes) {
    vector<pair<Node, vector<int>>> res;
    sort(nodes.begin(), nodes.end(), compar);
    for(Node n : nodes) {
        vector<int> tr;
        tr.resize(256,-1);
        for (Transition t: n.getTransitions()) {
            if(!t.getTransition().size())continue;
            if(!t.getTo().size())continue;
            int index =t.getTransition()[0];
            int value = stoi(t.getTo());
            if(!index)continue;
            if(!value)continue;
            tr[index]= value;
        }
        //pair<Node, int[256]> p=make_pair(n,int[](tr));
        res.push_back(make_pair(n,tr));
    }
    return res;
};
//
//vector<pair<Node, vector<int>>> DFA::get_saeed_array(vector<Node> nodes) {
//    vector<pair<Node, vector<int>>> res;
//    sort(nodes.begin(), nodes.end(), compar);
//    for(Node n : nodes) {
//        vector<int> tr;
//        tr.resize(256,-1);
//        for (Transition t: n.getTransitions()) {
//            if(t.getTo().size())continue;
//            if(t.getTransition().size())continue;
//            int index =t.getTransition()[0];
//            int value = stoi(t.getTo());
//            if(!index)continue;
//            if(!value)continue;
//            tr[index]= value;
//        }
//        //pair<Node, int[256]> p=make_pair(n,int[](tr));
//        res.push_back(make_pair(n,tr));
//    }
//    return res;
//}