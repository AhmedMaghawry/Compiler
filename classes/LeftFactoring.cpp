//
// Created by arsanuos on 25/04/18.
//
#define terminal true
#define non_terminal false
#define empty_str    ""

#include "../headers/LeftFactoring.h"



map<string, vector<vector<pair<string, bool>>>> LeftFactoring::factor(map<string, vector<vector<pair<string, bool>>>> grammar) {
    bool try_again = true;
    while(try_again){
        grammar = immediate_left_factoring(grammar, try_again);
    }

    //print_grammar(grammar);
    return grammar;
}

map<string, vector<vector<pair<string, bool>>>>  LeftFactoring::immediate_left_factoring(map<string, vector<vector<pair<string, bool>>>> &grammar, bool &try_again){
    map<string, vector<vector<pair<string, bool>>>> new_grammar;
    int out = 0;
    for(auto it  = grammar.begin(); it != grammar.end(); it++){
        vector<vector<pair<string, bool>>> new_all_choices;
        int count = 1;
        string original_production_name = it->first;
        vector<vector<pair<string, bool>>> &all_choices = it->second;
        bool modified = false;
        while(true){
            /**
             * get common string in position zero and remove it.
             */
            vector<vector<pair<string, bool>>> new_line_choices;
            string str = get_common_in_position_zero(all_choices, new_line_choices);
            /**
             * after the previous method
             * 1- all_choices contains the choices that have consider of any common between them.
             * 2- the new_line_choices will contains every choice was considered to have a common among it.
             * 3- the new_line_choices will be considered for any common between them.
             */
            if(str.empty()) break;
            /**
             * add one choice to all choices that contains for example
             *  int method_body0
             *
             */
            out++;
            modified = true;
            vector<pair<string, bool>> choice;
            choice.push_back(make_pair(str, terminal));
            choice.push_back(make_pair(original_production_name + to_string(count), non_terminal));
            all_choices.push_back(choice);
            new_grammar.insert(make_pair(original_production_name + to_string(count - 1), all_choices));
            count++;
            /**
              * In the next we will replace the all_choices to be new_line_choice.
              */
            all_choices = new_line_choices;
            //print_grammar(new_grammar);
        }
        /**
         * add rest of previous choices.
         */
        if(!modified){
            new_grammar.insert(make_pair(original_production_name, all_choices));
        }else if(!all_choices.empty()){
            //print_grammar(new_grammar);
            new_grammar.insert(make_pair(original_production_name + to_string(count - 1), all_choices));
        }
    }
    if(out == 0){
        try_again = false;
    }
    print_grammar(new_grammar);
    return new_grammar;
}

void LeftFactoring::print_grammar(map<string, vector<vector<pair<string, bool> > > > &grammar){
    cout<< "----------------"<<endl;
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



string LeftFactoring::get_common_in_position_zero(vector<vector<pair<string, bool>>> &all_choices, vector<vector<pair<string, bool>>> &new_line_choices){
    //TODO: we need to get the common string and modify all_choices in the way of removing common from the first
    //TODO: and get the new line we will consider next loop.
    string common;
    int count = 0;
    for(auto &choice : all_choices){
        if(choice[0].second){
            if(count == 0){
                common = choice[0].first;
                count = 1;
            }else{
                if(choice[0].first == common){
                    count++;
                }else{
                    count--;
                }
            }
        }
    }
    count = 0;
    for(auto &choice : all_choices){
        if(choice[0].second){
            if(common == choice[0].first){
                count++;
            }
        }
    }
    if(count == 1) return empty_str;
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
            }
            i--;
        }
    }
    return common;
}