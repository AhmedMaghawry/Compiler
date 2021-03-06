//
// Created by arsanuos on 25/04/18.
//
#define terminal true
#define non_terminal false
#define empty_str  make_pair("", false);
#define eps "\\L"

#include "../headers/LeftFactoring.h"



map<string, vector<vector<pair<string, bool>>>> LeftFactoring::factor(map<string, vector<vector<pair<string, bool>>>> grammar, vector<string> &non_terminals) {
    bool try_again = true;
    cout<< "-------------------factoring----------------"<<endl;
    print_grammar(grammar);
    while(try_again){
        grammar = immediate_left_factoring(grammar, try_again);
    }
    print_grammar(grammar);
    modify_non_terminals(grammar, non_terminals);
    return grammar;
}

map<string, vector<vector<pair<string, bool>>>>  LeftFactoring::immediate_left_factoring(map<string, vector<vector<pair<string, bool>>>> &grammar, bool &try_again){
    map<string, vector<vector<pair<string, bool>>>> new_grammar;
    int out = 0;
    for(auto it  = grammar.begin(); it != grammar.end(); it++){
        vector<vector<pair<string, bool>>> new_all_choices;
        unsigned long count = 1;
        string original_production_name = it->first;
        vector<vector<pair<string, bool>>> &all_choices = it->second;
        bool modified = false;
        while(true){
            /**
             * get common string in position zero and remove it.
             */
            vector<vector<pair<string, bool>>> new_line_choices;
            pair<string, bool> ret = get_common_in_position_zero(all_choices, new_line_choices);
            /**
             * after the previous method
             * 1- all_choices contains the choices that have consider of any common between them.
             * 2- the new_line_choices will contains every choice was considered to have a common among it.
             * 3- the new_line_choices will be considered for any common between them.
             */
            if(ret.first.empty()) break;
            /**
             * add one choice to all choices that contains for example
             *  int method_body0
             *
             */
            while(new_grammar.find(original_production_name + to_string(count - 1)) != new_grammar.end()){
                count++;
            }
            modify_current_terminals(original_production_name, grammar, original_production_name + to_string(count - 1));
            modify_current_terminals(original_production_name, new_grammar, original_production_name + to_string(count - 1));
            out++;
            modified = true;
            vector<pair<string, bool>> choice;
            choice.push_back(make_pair(ret.first, ret.second));
            choice.push_back(make_pair(original_production_name + to_string(count), non_terminal));
            all_choices.push_back(choice);
            new_grammar.insert(make_pair(original_production_name + to_string(count - 1), all_choices));
            count++;
            /**
              * In the next we will replace the all_choices to be new_line_choice.
              */
            all_choices = new_line_choices;
            modify_current_terminals(original_production_name, grammar, original_production_name + to_string(count - 2));
            modify_current_terminals(original_production_name, new_grammar, original_production_name + to_string(count - 2));
            //print_grammar(new_grammar);
        }
        /**
         * add rest of previous choices.
         */
        if(!modified){
            new_grammar.insert(make_pair(original_production_name, all_choices));
        }else if(!all_choices.empty()){
            //print_grammar(new_grammar);
            while(new_grammar.find(original_production_name + to_string(count - 1)) != new_grammar.end()){
                count++;
            }
            new_grammar.insert(make_pair(original_production_name + to_string(count - 1), all_choices));
        }
    }
    if(out == 0){
        try_again = false;
    }
    return new_grammar;
}

void LeftFactoring::print_grammar(map<string, vector<vector<pair<string, bool> > > > &grammar){
    cout<< "================================================================="<<endl;
    auto it  = grammar.begin();
    while(it != grammar.end()){
        string name = it->first;
        cout<< name << " " << "=";
        vector<vector<pair<string, bool>>> &choices = it->second;
        for(int i = 0 ;i < choices.size(); i++){
            vector<pair<string, bool>> &production = choices[i];
            for(int k = 0 ;k < production.size(); k++){
                cout << " " <<  production[k].first << " ";
            }
            cout<< "|";
        }
        cout<<endl;
        it++;
    }
}

void LeftFactoring::modify_non_terminals(map<string, vector<vector<pair<string, bool> > > > &grammar, vector<string> &non_terminals){
    set<string> new_non_terminals;
    string keep_first = non_terminals[0];
    auto it  = grammar.begin();
    while(it != grammar.end()){
        string name = it->first;
        vector<vector<pair<string, bool>>> &choices = it->second;
        for(int i = 0 ;i < choices.size(); i++){
            vector<pair<string, bool>> &production = choices[i];
            for(int k = 0 ;k < production.size(); k++){
                if(production[k].second == non_terminal){
                    new_non_terminals.insert(production[k].first);
                }
            }
        }
        it++;
    }
    non_terminals.clear();
    for(auto str : new_non_terminals){
        non_terminals.push_back(str);
    }
    std::reverse(non_terminals.begin(), non_terminals.end());
    non_terminals.push_back(keep_first);
    std::reverse(non_terminals.begin(), non_terminals.end());
}

bool LeftFactoring::size_of(vector<vector<pair<string, bool>>> &all_choices){
    if(all_choices.size() == 1){
        return true;
    }else if(all_choices.size() == 2 && all_choices[1][0].first == eps){
        return true;
    }
    return false;
}

pair<string, bool> LeftFactoring::get_common_in_position_zero(vector<vector<pair<string, bool>>> &all_choices, vector<vector<pair<string, bool>>> &new_line_choices){
    //TODO: we need to get the common string and modify all_choices in the way of removing common from the first
    //TODO: and get the new line we will consider next loop.
    if(size_of(all_choices)) return empty_str;
    string common;
    bool type;
    int count = 0;
    for(auto &choice : all_choices){
        if(count == 0){
            common = choice[0].first;
            type = choice[0].second;
            count = 1;
        }else{
            if(choice[0].first == common){
                count++;
            }else{
                count--;
            }
        }
    }
    count = 0;
    for(auto &choice : all_choices){
        if(common == choice[0].first){
            count++;
        }
    }
    if(count <= 1) return empty_str;
    if(common.empty()) return empty_str;
    for(int i = 0 ;i < all_choices.size();i++){
        vector<pair<string, bool>> choice = all_choices[i];
        if(choice[0].first == common){
            choice.erase(choice.begin());
            all_choices.erase(all_choices.begin() + i);
            /**
             * new choices for the new line.
             */
            if(!choice.empty()){
                new_line_choices.push_back(choice);
            }else{
                vector<pair<string, bool>> tmp;
                tmp.push_back(make_pair(eps, terminal));
                new_line_choices.push_back(tmp);
            }
            i--;
        }
    }
    return make_pair(common, type);
}

void LeftFactoring::modify_current_terminals(string str, map<string ,vector<vector<pair<string, bool>>>> &grammar, string new_string){
    for(auto it  = grammar.begin(); it != grammar.end(); it++){
        vector<vector<pair<string, bool>>> &choices = it->second;
        for(int i = 0 ;i < choices.size(); i++){
            vector<pair<string, bool>> &choice = choices[i];
            for(int j = 0 ;j < choice.size(); j++){
                if(choice[j].first == str){
                    choice[j].first = new_string;
                }
            }
        }
    }
}