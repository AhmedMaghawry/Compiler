//
// Created by arsanuos on 25/04/18.
//

#define terminal true
#define non_terminal false
#define eps "\\L"

#include "../headers/LeftRecursion.h"


map<string, vector<vector<pair<string, bool> > > > LeftRecursion::clean_left_recursion(map<string, vector<vector<pair<string, bool> > > > &grammar){
    // TODO::detect left recursion.
    // TODO::remove left recursion choices.
    // TODO::for each other productions add the non-terminal at the end.
    // TODO::add the removed production with the new non-terminal.
    // TODO::add eps.
    cout<< "-------------------recusion----------------"<<endl;
    print_grammar(grammar);
    int count = 0;
    map<string, vector<vector<pair<string, bool> > > > new_grammar;
    for(auto &all_choices : grammar) {
        string new_non_terminal = all_choices.first + to_string(count);
        vector<vector<pair<string, bool>>> new_line_choices = detect_and_delete_left_recursion(all_choices.second, all_choices.first, new_non_terminal);
        new_grammar.insert(make_pair(all_choices.first, all_choices.second));
        if(!(new_line_choices.size() == 1 && new_line_choices[0][0].first == eps)){
            new_grammar.insert(make_pair(new_non_terminal, new_line_choices));
        }

        count++;
    }
    print_grammar(new_grammar);
    return new_grammar;
}

void LeftRecursion::print_grammar(map<string, vector<vector<pair<string, bool> > > > &grammar){
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

vector<vector<pair<string, bool>>> LeftRecursion::detect_and_delete_left_recursion(vector<vector<pair<string, bool> > > &all_choices, string all_choice_first, string new_non_terminal){
    vector<vector<pair<string, bool>>> new_line_choices;
    for(int i = 0 ;i < all_choices.size(); i++){
        vector<pair<string, bool> > &choice = all_choices[i];
        if(!choice[0].second && all_choice_first == choice[0].first){
            /**
             * remove left recursion.
             */
            choice.erase(choice.begin());
            /**
             * add new_non_terminal
             */
            choice.push_back(make_pair(new_non_terminal, non_terminal));
            /**
             * add the choice to the new_line_choices.
             */
            new_line_choices.push_back(choice);
            /**
             * remove the whole choice from all_choices.
             */
            all_choices.erase(all_choices.begin() + i);
            i--;
        }else{
            choice.push_back(make_pair(new_non_terminal, non_terminal));
        }
    }
    if(all_choices.empty()) throw "error in syntax a production that never ends.";
    vector<pair<string, bool>> eps_vector;
    eps_vector.push_back(make_pair(eps, terminal));
    new_line_choices.push_back(eps_vector);
    return new_line_choices;
}