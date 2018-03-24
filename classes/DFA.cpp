//
// Created by default on 19/03/18.
//

#include <iostream>
#include <algorithm>
#include "../headers/DFA.h"

const string e ="\\L";
Node fi("");
vector<string> trans_symb;
vector<Node> nfaGraph;
vector<Node> nfa_without_e;

vector<Node> remove_e_clousre(vector<Node> graph);
void display_graph(vector<Node> nodes);
bool isAcceptance(Node node);
void e_clousre(vector<Node> &nodes, Node &node);

void remove_duplicates(vector<Node> &nodes);

void add_new_transitions(Node &node, vector<Node> vector);

Node getNode(string basic_string, vector<Node> list);

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
    display_graph(getDfaGraph());
}

void DFA::run_dfa(vector<Node> &final_graph, vector<Node> nfa_without_clousre) {
    Node start_node = nfa_without_clousre[0];
    queue<Node> q;
    //final_graph.push_back(start_node);
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
                new_node.addAcceptance(n.getAcceptance());
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
    //TODO:Add the Acceptance State
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
    for (int i = 0; i < size; ++i) {
        Node n(graph[i].getNumber());
        vector<Transition> trans = graph[i].getTransitions();
        vector<Node> nodes_by_ebs;
        Node temp = graph[i];
        e_clousre(nodes_by_ebs, temp);
        nodes_by_ebs.push_back(temp);
        remove_duplicates(nodes_by_ebs);
        add_new_transitions(n, nodes_by_ebs);
        res.push_back(n);
    }
    return res;
}

void add_new_transitions(Node &node, vector<Node> nodes) {
    for (string symb : trans_symb) {
        for (Node n : nodes) {
            for (Transition t : n.getTransitions()) {
                if(t.getTransition() == symb) {
                    vector<Node> nodes_in_final;
                    Node node_intermediate = getNode(t.getTo(), nfaGraph);
                    nodes_in_final.push_back(node_intermediate);
                    e_clousre(nodes_in_final, node_intermediate);
                    remove_duplicates(nodes_in_final);
                    for (Node final_node : nodes_in_final) {
                        Transition tran(final_node.getNumber() ,symb);
                        node.addTransitions(tran);
                        //node.addAcceptance(final_node.getAcceptance());
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

void e_clousre(vector<Node> &nodes, Node &node) {
    //DFS
    for (Transition transition : node.getTransitions()) {
        if(transition.getTransition() == e) {
            Node to_go_node = getNode(transition.getTo(), nfaGraph);
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