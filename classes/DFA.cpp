//
// Created by default on 19/03/18.
//

#include "../headers/DFA.h"

const string e ="\\L";
string trans_symb[10];
vector<Node> nfaGraph;

vector<Node> remove_e_clousre(vector<Node> graph);
void e_clousre(vector<Node> &nodes, vector<Transition> trans);

void remove_duplicates(vector<Node> &nodes);

void add_new_transitions(Node &node, vector<Node> vector);

Node getNode(string basic_string);

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
void DFA::convert_from_NFA_to_DFA(vector<Node> graph) {
    nfaGraph = graph;
    vector<Node> nfaGraph_without_clouser = remove_e_clousre(graph);
    vector<Node> dfaGraph_final;
    setDfaGraph(dfaGraph_final);
}

/*
 * Remove the E clousre which take the NFA graph
 * and return NFA but without E clousre
 */
vector<Node> remove_e_clousre(vector<Node> graph) {
    int size = graph.size();
    //vector<Node> res(size);
    vector<Node> res;
    for (int i = 0; i < size; ++i) {
        Node n(graph[i].getNumber());
        vector<Transition> trans = n.getTransitions();
        //vector<Node> nodes_by_ebs(trans.size());
        vector<Node> nodes_by_ebs;
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
                        Transition t(nodes_in_final[l].getNumber() ,trans_symb[i]);
                        node.addTransitions(t);
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

}

void e_clousre(vector<Node> &nodes, vector<Transition> trans) {
    for (int i = 0; i < trans.size() ; ++i) {
        Transition transition = trans[i];
        if(transition.getTransition() == e) {
            nodes.push_back(transition.getTo());
            e_clousre(nodes, getNode(transition.getTo()).getTransitions());
        }
    }
}

Node getNode(string node_name) {
    for(Node i : nfaGraph) {
        if(i.getNumber() == node_name)
            return i;
    }
}