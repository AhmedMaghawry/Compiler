//
// Created by arsanuos on 22/03/18.
//

#ifndef COMPILER_OPERATIONHANDLER_H
#define COMPILER_OPERATIONHANDLER_H

#include <string>

using namespace std;

class OperationHandler {

private:
    static const string valid_operations;

public:
    static bool isOperation(string oper);
    static int precedence(string oper);
    static bool isUnary(string operation);
};


#endif //COMPILER_OPERATIONHANDLER_H