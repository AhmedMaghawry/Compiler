//
// Created by default on 19/03/18.
//

#include <algorithm>
#include "../headers/DFA.h"

const char e ='-1';
char trans_symb[10];

vector<Node> remove_e_clousre(vector<Node> graph);
void e_clousre(vector<Node> &nodes, vector<Transition> trans);

void remove_duplicates(vector<Node> &nodes);

void add_new_transitions(Node &node, vector<Node> vector);

const vector<Node> &DFA::getDfaGraph() const {
    return dfaGraph;
}

/*
 * Use subset Construction Algorithm to convert
 * the graph from NFA to DFA as a vector
 * of Nodes which contain the transition
 */
void convert_from_NFA_to_DFA(vector<Node> graph) {
    vector<Node> nfaGraph = graph;
    nfaGraph = remove_e_clousre(graph);

}

/*
 * Remove the E clousre which take the NFA graph
 * and return NFA but without E clousre
 */
vector<Node> remove_e_clousre(vector<Node> graph) {
    int size = graph.size();
    vector<Node> res(size);
    for (int i = 0; i < size; ++i) {
        Node n = Node::Node(graph[i].getNumber());
        vector<Transition> trans = n.getTransitions();
        vector<Node> nodes_by_ebs(trans.size());
        e_clousre(nodes_by_ebs, trans);
        remove_duplicates(nodes_by_ebs);
        add_new_transitions(n, nodes_by_ebs);
        res.push_back(n);
    }
    return res;
}

void add_new_transitions(Node &node, vector<Node> nodes) {
    for (int i = 0; i < sizeof(trans_symb); ++i) {
        for (int j = 0; j < nodes.size(); ++j) {
            for (int k = 0; k < nodes[j].getTransitions().size(); ++k) {
                if(nodes[j].getTransitions()[k].getTransition() == trans_symb[i]) {
                    vector<Node> nodes_in_final;
                    e_clousre(nodes_in_final, nodes[j].getTransitions());
                    for (int l = 0; l < nodes_in_final.size(); ++l) {
                        node.addTransitions(Transition::Transition(nodes_in_final[l] ,trans_symb[i]));
                        for (int m = 0; m < nodes_in_final[l].getAcceptance().size(); ++m) {
                            node.addAcceptance(nodes_in_final[l].getAcceptance()[m]);
                        }
                    }
                }
            }
        }
    }
}

void remove_duplicates(vector<Node> &nodes){
    std::sort(nodes.begin(), nodes.end());
    auto last = std::unique(nodes.begin(), nodes.end());
    nodes.erase(last, nodes.end());
}

void e_clousre(vector<Node> &nodes, vector<Transition> trans) {
    for (int i = 0; i < trans.size() ; ++i) {
        Transition transition = trans[i];
        if(transition.getTransition() == e) {
            nodes.push_back(transition.getTo());
            e_clousre(nodes, transition.getTo().getTransitions());
        }
    }
}