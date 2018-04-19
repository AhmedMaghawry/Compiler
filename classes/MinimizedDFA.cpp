//
// Created by marwan on 21/03/18.
//


#include "../headers/MinimizedDFA.h"
#include<bits/stdc++.h>
#include <set>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

Node getNodeInDFA(string node_name,vector <Node> dfa );
//bool  sortbysec( Transition & a,Transition & b);
//bool  sortbyname( Node &a,Node &b);
MinimizedDFA::MinimizedDFA ( vector<Node> unmin){
    unminimizedDFA=unmin;
}

vector <Node> MinimizedDFA::getUnminimizedDFA (){
    return unminimizedDFA;
}
Node MinimizedDFA::getStartNode() {
    if(unminimizedDFA.size()>0)
        return unminimizedDFA[0];
}
bool MinimizedDFA::isAcceptence(Node node) {
    if(node.getAcceptance().first==-1)
        return  false;
    return true;
}
vector <Node> MinimizedDFA::evaluateMinimized() {
    vector <Node> set1 ;
    vector <Node> finalMinDFa;
    //vector < vector <Node> > total;
    // std::cout<<unminimizedDFA.size()<<"testttt";
    sortTranstions(unminimizedDFA);  //هنااااااا
    for(int i=0;i<unminimizedDFA.size();i++){
        if(isAcceptence(unminimizedDFA[i])){
            unminimizedDFA[i].setGroupNumber("2");
            set1.push_back(unminimizedDFA[i]);
        }

        else{
            unminimizedDFA[i].setGroupNumber("1");
            set1.push_back(unminimizedDFA[i]);
        }

    }
    updateMinimizedDFA(set1);
    while (!isMinimum(set1)){
        updateMinimizedDFA(set1);
    }
//    for(int i=0;i<set1.size();i++){
//        cout << set1[i].getNumber()<<" gNum "<<set1[i].getGroupNumber() <<" tNum "<< set1[i].getTotalGroupNumber()<<"\n";
//    }
    finalMinDFa = createMinDFA(set1);
//    for(int i=0;i<finalMinDFa.size();i++){
//       cout << finalMinDFa[i].getNumber()<<" gNum "<<finalMinDFa[i].getGroupNumber() <<" tNum "<< finalMinDFa[i].getTotalGroupNumber()
//            <<"transs = "<<finalMinDFa[i].getTransitions().size()<<"\n";
//  }
    return normalizedMinDFA(finalMinDFa);
}
//


Node getNodeInDFA(string node_name,vector <Node> dfa ) {
    for(Node i : dfa) {
        if(i.getNumber() == node_name)
            return i;
    }
    Node fi("");
    return fi;
}
vector <Node> MinimizedDFA:: calculateRelations (vector <Node> & set1) {

    string s;
    string v = "";

    for (int i = 0; i < set1.size(); i++) {
        for (int j = 0; j < set1[i].getTransitions().size(); j++) {
            s = set1[i].getTransitions()[j].getTo();
            Node x = getNodeInDFA(s, set1);
            if(x.getGroupNumber() == "-1") {
                v.append("0");
            } else
                v.append(x.getGroupNumber());
        }
        set1[i].setTotalGroupNumber(v);
        v = "";
    }

    return set1;
}
bool MinimizedDFA ::isMinimum( vector <Node> set1){
    set < pair<string,string> > undup1;
    for(int j=0;j<set1.size();j++){
        undup1.insert(make_pair(set1[j].getTotalGroupNumber(),set1[j].getGroupNumber()));
    }
    for (auto it = undup1.begin(); it != undup1.end(); ++it){
        //std::cout<<*it<<" ";
        for(int i=0;i<set1.size();i++){
            if(it->first!=set1[i].getTotalGroupNumber()&& it->second==set1[i].getGroupNumber()){
                return  false;
            }
        }
    }
    return true;
}
void MinimizedDFA:: sortTranstions(vector<Node> & unminiDFA){
    int n=unminiDFA.size();
    vector<Node> ans;
    // cout<<"\nn"<<n;
    for(int i=0;i<n;i++){
        //   cout<< unminiDFA.size();
        vector <Transition> temp=unminiDFA[i].getTransitions();
        sort(temp.begin(),temp.end(),sortbysec);
        //cout<<temp[0].getTransition()<<" "<<temp[1].getTransition()<<"\n";
        unminiDFA[i].setTransitions(temp);
    }
}
/*bool  sortbysec(  Transition &a, Transition &b)
{
   return (a.getTransition() < b.getTransition());
}
*/
//bool  sortbyname( Node &a,Node &b)
//{
//    return (a.getNumber()< b.getNumber());
//}

void MinimizedDFA:: updateMinimizedDFA (vector<Node>&set1){
    vector <Node> eachSet ;
    set <pair<string,string>> undup1;
    int counter=0;
    int maxGroupNum=-100000;
    eachSet= calculateRelations(set1) ;
    vector <Node> editedSet =eachSet;
    vector <Node> finalEditSet;
    for(int j=0;j<eachSet.size();j++){
        int groupNum =stoi(eachSet[j].getGroupNumber());
        if(maxGroupNum < groupNum )
            maxGroupNum =groupNum;
        undup1.insert(make_pair(eachSet[j].getTotalGroupNumber(),eachSet[j].getGroupNumber()));
    }
    for (auto it = undup1.begin(); it != undup1.end(); ++it){
        //std::cout<<*it<<" ";
        for(int i=0;i<eachSet.size();i++){
            if(it->first==eachSet[i].getTotalGroupNumber()&& it->second==eachSet[i].getGroupNumber()){
                editedSet[i].setGroupNumber(to_string(counter+1));
            }
        }
        counter++;
    }
    finalEditSet=calculateRelations(editedSet);
    set1=finalEditSet;
}

//void MinimizedDFA:: sortToNodes(vector <vector <Node>>& all) {
//    for (int i=0;i<all.size();i++){
//        sort(all[i].begin(),all[i].end(),sortbyname);
//    }
//
//}
vector<Node> MinimizedDFA:: createMinDFA (vector <Node> & all) {
    int firstNodeIndex;
    Node firstNode("");
    bool found= false;
    string states="";
    string to="";
    vector<Node> ans;
//    vector<Node> acceptedNodes;
//    vector<Node> removedDuplicateAll;
    int duplicateNum=0;
    for (int i=0;i<all.size()&&!found;i++){
        if(all[i].getNumber()==getStartNode().getNumber()){
            firstNodeIndex=i;
            firstNode=all[i];
            //removedDuplicateAll.push_back(all[i]);
            found= true;
        }
    }
    // cout <<firstNodeIndex<<" index \n";
//    for(int i=0;i<all.size();i++){
//        relateMap.insert(make_pair(i,(char))
//    }
    Node start(all[firstNodeIndex].getGroupNumber());
    states= all[firstNodeIndex].getTotalGroupNumber();
    start.addAcceptance(all[firstNodeIndex].getAcceptance());
    start.setGroupNumber(all[firstNodeIndex].getGroupNumber());
    start.setTotalGroupNumber(all[firstNodeIndex].getTotalGroupNumber());
    for(int j=0;j<states.length();j++) {
        to=states[j];
        Transition minTran=Transition(to,all[firstNodeIndex].getTransitions()[j].getTransition());
        // cout<<all[firstNodeIndex].getTransitions()[j].getTransition()<<" here1\n";
        //  cout<<to<<"hereeeee\n";
        start.addTransitions(minTran);
    }
    ans.push_back(start);
    for (int i=0;i<all.size();i++){
        if(i==firstNodeIndex) continue;
        Node n (all[i].getGroupNumber());
        if(  isAcceptence(all[i])){
            n.addAcceptance(all[i].getAcceptance());
        }
        n.setTotalGroupNumber(all[i].getTotalGroupNumber());
        n.setGroupNumber(all[i].getGroupNumber());
        states= all[i].getTotalGroupNumber();
        for(int j=0;j<states.length();j++) {
            to=states[j];
            Transition minTran=Transition(to,all[i].getTransitions()[j].getTransition());
            n.addTransitions(minTran);
        }
        ans.push_back(n);
    }

    for(int i=0;i<ans.size();i++){

    }
    return ans;

}

vector<Node> MinimizedDFA:: normalizedMinDFA(vector <Node> & all){
    std::set<Node> nodeSet;
    //std::set<Node>::iterator nit;
    vector <Node> normaliziedAns;
    Node firstNode = all[0];
    for(int i=0;i<all.size();i++){
        nodeSet.insert(all[i]);
    }
    for(auto nit = nodeSet.begin(); nit != nodeSet.end(); nit++) {
        Node n=*(nit);
        string st1=n.getTotalGroupNumber();
        string st2=n.getGroupNumber();
        if(firstNode.getTotalGroupNumber()==st1&&
           firstNode.getGroupNumber()==st2 ){
            normaliziedAns.push_back((*nit));
            nodeSet.erase(nit);
            break;
        }
    }
    for(auto nit = nodeSet.begin(); nit != nodeSet.end(); nit++)
        normaliziedAns.push_back((*nit));
    return normaliziedAns;
}




/*using namespace std;

int main() {
    Node A("A");
    Node B("B");
    Node C("C");
    Node D("D");
    Node E("E");

    A.addAcceptance(make_pair(-1,"no"));
    B.addAcceptance(make_pair(-1,"no"));
    C.addAcceptance(make_pair(-1,"no"));
    D.addAcceptance(make_pair(-1,"no"));
    E.addAcceptance(make_pair(1,"yes"));

    A.addTransitions(Transition("B","+"));
    A.addTransitions(Transition("C","-"));
    B.addTransitions(Transition("B","+"));
    B.addTransitions(Transition("D","-"));
    C.addTransitions(Transition("C","-"));
    C.addTransitions(Transition("B","+"));
    D.addTransitions(Transition("E","-"));
    D.addTransitions(Transition("B","+"));
    E.addTransitions(Transition("C","-"));
    E.addTransitions(Transition("B","+"));

    vector<Node> test;
    test.push_back(A);
    test.push_back(B);
    test.push_back(C);
    test.push_back(D);
    test.push_back(E);



    MinimizedDFA unmin(test);
    vector<Node> ans = unmin.evaluateMinimized();///hena
    //unmin.sortTranstions(test);
    // cout<<unmin.getUnminimizedDFA().size();
    cout<<ans.size()<<"\n";
    for(int i=0;i<ans.size();i++){
        cout<<"state "<<ans[i].getNumber()<<" trans = " <<ans[i].getTransitions().size()<<"\n";
        for(int j=0;j<ans[i].getTransitions().size();j++){
            cout<<"To" <<ans[i].getTransitions()[j].getTo()<<"input "
                <<ans[i].getTransitions()[j].getTransition()<<"\n";
        }
    }




    return 0;
}
*/