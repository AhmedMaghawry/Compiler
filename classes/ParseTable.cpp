//
// Created by marwan on 24/04/18.
//

#include <iostream>
#include <bits/stdc++.h>
#include "../headers/ParseTable.h"
using namespace std;


ParseTable::ParseTable( map<string, vector<pair<string, vector<pair<string, bool>>>>> firstMap,
                       map<string, vector<string>> followMap, vector<string> nonTermin, vector<string> termin)  {
    first=firstMap;
    follow=followMap;
    terminals=termin;
    nonTerminals=nonTermin;
    epsilonRule.push_back(make_pair(e,true));
    syncRule.push_back(make_pair("sync",true));
    errorRule.push_back(make_pair("error", true));
}

 vector<string> ParseTable::getNonTerminals()  {
    return nonTerminals;
}

 vector<string> ParseTable::getTerminals()  {
    return terminals;
}

bool ParseTable:: isTerminal (string s){
    for(int i=0;i<terminals.size();i++){
        if(s==terminals[i])
            return true;
    }
    return false;
}

map<pair<string, string>, vector<pair<string, bool>> > ParseTable::getParseTable() {
    map<pair<string, string>, vector<pair<string, bool>> > ans;
    string nontermin;
    string termin;
    vector<pair<string, vector<pair<string, bool> > > >firsts;
    vector<pair<string, bool> > rules;
    vector <string> follows;
    pair<string, string> keys;
    //Intialize parse table
       for(int i=0;i<nonTerminals.size();i++){

        for(int j=0;j<terminals.size();j++){
            if(terminals[j]==e) continue;
            ans[make_pair(nonTerminals[i],terminals[j])]= rules;
        }
    }
    //adding firstmap to parse table
    for(auto it =first.begin();it!=first.end();++it){
         nontermin = it->first;
         firsts = it->second;
        for(int i=0;i<firsts.size();i++){
            termin= firsts[i].first;
            rules = firsts[i].second;
            // if nonterminal goes to epsilon
            if(termin == e){
                follows=follow[nontermin];
                for(int j=0;j<follows.size();j++){
                    ans[make_pair(nontermin,follows[j])]=epsilonRule;
                    //cout<<"epslion here"<<endl;
                }
            } else{
                ans[make_pair(nontermin,termin)]=rules;
            }
        }
    }
    //adding sync values to parseTable
    /*for(auto it =follow.begin();it!=follow.end();++it) {
        vector<pair<string, bool> > remainRule;
         nontermin=it->first;
        follows=follow[nontermin];
        if(follows.size()!=0){
            for(int j=0;j<follows.size();j++){
                ans[make_pair(nontermin,follows[j])]=syncRule;
            }
        }
    }*/
    //adding error values to parseTable
    for(int i=0;i<nonTerminals.size();i++){
        for(int j=0;j<terminals.size();j++){
            rules = ans[make_pair(nonTerminals[i],terminals[j])];
            if(rules.size()==0)
                ans[make_pair(nonTerminals[i],terminals[j])]=errorRule;
        }
    }
    return ans;
}

map<pair<string, string>, vector<pair<string, bool>> > ParseTable::getParseTable_Ezzat() {
    map<pair<string, string>, vector<pair<string, bool>> > ans;
    for (int i = 0; i < nonTerminals.size(); ++i) {
        for (int k = 0; k < first[nonTerminals[i]].size(); ++k) {
            if(first[nonTerminals[i]][k].first != e) {
                ans.insert(make_pair(make_pair(nonTerminals[i], first[nonTerminals[i]][k].first), first[nonTerminals[i]][k].second));
            } else {
                for (int j = 0; j < follow[nonTerminals[i]].size(); ++j) {
                    ans.insert(make_pair(make_pair(nonTerminals[i], follow[nonTerminals[i]][j]), epsilonRule));
                }
            }
        }
    }
    return ans;
}

vector<pair<string, bool> > ParseTable:: getEpsilonRule(){
    return epsilonRule;
}

vector<pair<string, bool> >  ParseTable:: getSyncRule(){
    return syncRule;
}
vector<pair<string, bool> > ParseTable:: getErrorRule(){
    return errorRule;
}

bool ParseTable:: isValidParseTable(){
    multimap <pair <string,string> ,int> ruleCount;
    for(int i=0;i<nonTerminals.size();i++) {
        for (int j = 0; j < terminals.size(); j++) {
          //  if()
          //  ruleCount.insert(make_pair(nonTerminals[i],terminals[j]),1);
        }
    }
    for(int i=0;i<nonTerminals.size();i++) {
        for (int j = 0; j < terminals.size(); j++) {

        }
    }
}


/* bool ParseTable:: sortbyfirst(  pair<string, bool> &a, pair<string, bool> &b)
{
    return (a.first < b.first);
}*/