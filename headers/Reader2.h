/*
 * Reader2.h
 *
 *  Created on: Mar 18, 2018
 *      Author: saed
 */

#ifndef READER2_H_
#define READER2_H_


#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;


class Reader
{
public:
    // Instance variables
    string fileName;
    vector <string> readingLines;

    // Functions to read file name
    void readFiletoLines(string fileName);
    vector <char> readStringtoCharacters(string lines);
};
// Class to write to file
class Writer
{
public:
    // Instance variables
    string fileName;

    // Functions to read file name
    void writeLinesToFile(string fileName, vector <string> lines);
    void writeStringToFile(string fileName, string line);
};

#endif /* READER2_H_ */