/*
 * Reader2.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: saed
 */

#include "../headers/Reader2.h"


void Writer:: writeLinesToFile(string fileName, vector <string> lines)
{

    // Object to write in file
    ofstream file_obj;

    // Opening file in append mode
    const char * fName =  fileName.c_str();
    file_obj.open(fName, ios::out);
    //cout <<"hellllo"<<endl;

    for(std::vector<std::string>::const_iterator it = lines.begin(); it != lines.end(); ++it)
    {
        string value = *it;
        cout<<*it<<endl;
        const char * consValue =  value.c_str();
        file_obj.write(consValue, value.size());
        file_obj << "\n";
        // cout <<"hellllo"<<endl;
    }
    file_obj.close();
}
void Writer:: writeStringToFile(string fileName, string line)
{
    // Object to write in file
    ofstream file_obj;

    // Opening file in append mode
    const char * fName =  fileName.c_str();
    file_obj.open(fName, ios::out);


    const char * consValue =  line.c_str();
    file_obj.write(consValue, line.size());
    file_obj.close();

}
// Read from file and get a vector of strings
void Reader:: readFiletoLines (string fileName)
{
    string line;
    vector <string> answer ;
    // Object to read from file

    // Opening file in input mode
    const char * fName =  fileName.c_str();

    cout<<fName<<endl;
    ifstream file_obj ;
    file_obj.open(fName, ios::in);
    if (!file_obj.is_open())
        perror("error while opening file");
    else
    {

        while(getline(file_obj, line))
        {
            //cout <<"hi"<<endl;
            answer.push_back(line);
        }
        file_obj.close();
    }

    cout<<answer.size()<<"  hi"<<endl;
    readingLines = answer;

}
//Read character from a given string
vector <char> Reader:: readStringtoCharacters(string line)
{
    vector <char> answer ;
    // Object to read from file
    ifstream file_obj;

    // Opening file in input mode
    const char * fName =  fileName.c_str();
    file_obj.open(fName, ios::in);

    if (!file_obj.is_open())
        perror("error while opening file");
    else
    {
        for(std::string::iterator it = line.begin(); it != line.end(); ++it)
        {
            answer.push_back(*it);
        }
        file_obj.close();
    }


    return answer;
}
int main11()
{
    Reader R1 ;

    R1.readFiletoLines("input.txt");

    vector <string> ans  = R1.readingLines;
    Writer W1 ;
    W1.writeLinesToFile("output.txt",ans);
    return 0;
}
