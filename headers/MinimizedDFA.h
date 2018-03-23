//
// Created by marwan on 21/03/18.
//

#ifndef COMPILER_MINIMIZEDDFA_H
#define COMPILER_MINIMIZEDDFA_H


#include "Node.h"

class MinimizedDFA {
public:
    MinimizedDFA( vector<Node> unmin);
    Node getStartNode ();
    vector <Node> getUnminimizedDFA ();
    vector <Node> evaluateMinimized();
   // vector <vector<Node>> partitionSets (vector <Node> set1 , vector <Node> set2 ) ;
    vector <Node> calculateRelations (vector <Node> &set1);
    void  updateMinimizedDFA (vector<Node>&set1);
    void sortTranstions(vector<Node> & unminimizedDFA);
   static bool  sortbysec( Transition a,Transition b){ return (a.getTransition() < b.getTransition());}
    //static bool  sortbyname( Node a,Node b);
    vector<Node> normalizedMinDFA(vector <Node> & all);
    vector<Node> createMinDFA(vector <Node> & all);
    bool isMinimum( vector <Node> set);
    void  sortToNodes(vector <vector <Node>> &all);
    vector <Node> unminimizedDFA ;
    bool isAcceptence(Node node);
};
#endif //COMPILER_MASTER_MINIMIZEDDFA_H
