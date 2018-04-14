//
// Created by arsanuos on 22/03/18.
//
#define ccat "concat"

#include "../headers/OperationHandler.h"
#include <iostream>

const string OperationHandler::valid_operations = "-|+*";


bool OperationHandler::isOperation(string oper) {
    if(valid_operations.find(oper) != std::string::npos){
        return true;
    }else if(oper == ccat){
        return true;
    }
    return false;
}


int OperationHandler::precedence(string oper){
    if(!isOperation(oper)){
        throw "precedence for non-operation input";
    }
    if(oper == ccat){
        return 3;
    }else if(oper == "*"){
        return 4;
    }else if(oper == "+"){
        return 4;
    }else if(oper == "-"){
        return 2;
    }else if(oper == "|"){
        return 1;
    }

}

bool OperationHandler::isUnary(string operation){
    if(!isOperation(operation))
        throw "non-operation to be unary";
    if(operation == "*" || operation == "+"){
        return true;
    }
    return false;
}



