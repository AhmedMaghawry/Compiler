//
// Created by default on 23/04/18.
//

#include "../headers/First_Follow.h"

bool flag = true;

First_Follow::First_Follow(map<string, vector<vector<pair<string, bool>>>> grammer, vector<string> n_terminals, vector<string> terminals) {
    this->grammer = grammer;
    this->n_terminals = n_terminals;
    this->terminals = terminals;
}

void First_Follow::calculate_firsts() {
    for (int i = 0; i < n_terminals.size(); ++i) {
        if (!firstMap.count(n_terminals[i]))
            firstMap.insert(make_pair(n_terminals[i], First(n_terminals[i])));
    }
}

set<pair<string, vector<pair<string, bool>>>> First_Follow::First(string name) {
    set<pair<string, vector<pair<string, bool>>>> res;
    vector<vector<pair<string, bool>>> str = grammer[name];

    if (firstMap.count(name))
        return firstMap[name];

    //Loop on ORing
    for (int i = 0; i < str.size(); ++i) {
        //First Symbol in the production
        pair<string, bool> first_symbol = str[i][0];

        //If The same symbols A --> A..
        if(first_symbol.first == name) {
            //res.push_back(e);
            continue;
        }

        //If Terminal
        if (first_symbol.second) {
            res.insert(make_pair(first_symbol.first, str[i]));
        } else {
            //If Non Terminal
            set<pair<string, vector<pair<string, bool>>>> result_of_sub;

            if (!firstMap.count(first_symbol.first)) {
                //Not Calculated Before
                result_of_sub = First(first_symbol.first);
                firstMap.insert(make_pair(first_symbol.first, result_of_sub));
            } else {
                //Calculated Before
                result_of_sub = firstMap[first_symbol.first];
            }

            result_of_sub = repair_for_e(result_of_sub, str[i]);
            concat(res, result_of_sub);
        }
    }
    return res;
}

void First_Follow::concat(set<string> &res, set<string> add) {
    //res.reserve(res.size() + add.size());
    res.insert(add.begin(), add.end());
}

void First_Follow::concat(set<pair<string, vector<pair<string, bool>>>> &res, set<pair<string, vector<pair<string, bool>>>> add){
    //res.reserve(res.size() + add.size());
    res.insert(add.begin(), add.end());
}

set<pair<string, vector<pair<string, bool>>>> First_Follow::repair_for_e(set<pair<string, vector<pair<string, bool>>>> vals, vector<pair<string, bool>> symboles){
    int shifter = 1;
    set<pair<string, vector<pair<string, bool>>>> res;

    set<pair<string, vector<pair<string, bool>>>>:: iterator it;
    for( it = vals.begin(); it!=vals.end(); ++it){
        if (it->first == e){
            if (symboles.size() <= shifter) {
                //If All NT go to E
                res.insert(make_pair(e, symboles));
            } else {
                pair<string, bool> sym = symboles[shifter];
                if (sym.second)
                    res.insert(make_pair(sym.first, symboles));
                else
                    concat(res, First(sym.first));
                shifter++;
            }
        } else {
            res.insert(*it);
        }
    }
    return res;
}

void First_Follow::calculate_follows() {
    for (int i = 0; i < n_terminals.size(); ++i) {
        if (!followMap.count(n_terminals[i]))
            followMap.insert(make_pair(n_terminals[i], Follow(n_terminals[i])));
    }
}

set<string> First_Follow::Follow(string name) {
    set<string> res;

    if(flag) {
        res.insert("$");
        flag = false;
    }

    if(followMap.count(name))
        return followMap[name];

    map <string, vector<vector<pair<string, bool>>>>::iterator it;
    //Loop on all Rules
    for ( it = grammer.begin(); it != grammer.end(); it++ )
    {
        //Loop on Oring
        for (int i = 0; i < it->second.size(); ++i) {
            //Loop on a rule elements
            for (int j = 0; j < it->second[i].size(); ++j) {
                if (it->second[i][j].first == name) {
                    if (j == it->second[i].size() - 1) {
                        //If B --> ..A then the Follow(A) = Follow(B)
                        set<string> res_sub;
                        if (!followMap.count(it->first)) {
                            //Not Calculated Before
                            res_sub = Follow(it->first);
                            followMap.insert(make_pair(it->first, res_sub));
                        } else {
                            //Calculated Before
                            res_sub = followMap[it->first];
                        }
                        concat(res, res_sub);
                    } else {
                        //If B --> xAy
                        set<string> res_sub;
                        if(it->second[i][j + 1].second) {
                            res.insert(it->second[i][j + 1].first);
                        } else {
                            res_sub = replace_e_for_follow(firstMap[it->second[i][j + 1].first], it->first);
                        }
                        concat(res, res_sub);
                    }
                }
            }
        }
    }
    return res;
}

set<string> First_Follow::replace_e_for_follow(set<pair<string, vector<pair<string, bool>>>> li, string rule) {
    set<string> res;
    set<pair<string, vector<pair<string, bool>>>>:: iterator it;
    for( it = li.begin(); it!=li.end(); ++it){
        if(it->first == e) {
            if(!followMap.count(rule)){
                set<string> r = Follow(rule);
                followMap.insert(make_pair(rule,r));
                concat(res, r);
            } else {
                concat(res, followMap[rule]);
            }
        } else {
            res.insert(it->first);
        }
    }
    return res;
}

map<string, vector<pair<string, vector<pair<string, bool>>>>> First_Follow::getFirstMap() {
    map<string, vector<pair<string, vector<pair<string, bool>>>>> res;
    map <string,  set<pair<string, vector<pair<string, bool>>>> >::iterator it;
    for ( it = firstMap.begin(); it != firstMap.end(); it++ )
    {
        vector<pair<string, vector<pair<string, bool>>>> r;
        set<pair<string, vector<pair<string, bool>>>>:: iterator it2;
        for( it2 = it->second.begin(); it2!=it->second.end(); ++it2){
            r.push_back(*it2);
        }
        res.insert(make_pair(it->first,r));
    }
    return res;
}

map<string, vector<string>> First_Follow::getFollowMap() {
    map<string, vector<string>> res;
    map <string,  set<string> >::iterator it;
    for ( it = followMap.begin(); it != followMap.end(); it++ )
    {
        vector<string> r;
        set<string>:: iterator it2;
        for( it2 = it->second.begin(); it2!=it->second.end(); ++it2){
            r.push_back(*it2);
        }
        res.insert(make_pair(it->first,r));
    }
    return res;
}