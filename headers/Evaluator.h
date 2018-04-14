//
// Created by arsanuos on 21/03/18.
//

#ifndef COMPILER_EVALUATOR_H
#define COMPILER_EVALUATOR_H

#include "NFA.h"

class Evaluator {

public:
    static NFA oring(NFA a, NFA b);
    static NFA concat(NFA a, NFA b);
    static NFA star(NFA a);
    static NFA plus(NFA a);
    static NFA dash(NFA a, NFA b);
    static int convert(string exp);

private:
    static NFA scaleUP(NFA a, int n);
    static NFA addToFirst(NFA a, NFA b);
    static string getNewEndNodeNumber(NFA a, NFA b);
    static void printGraph(NFA a);
};


#endif //COMPILER_EVALUATOR_H