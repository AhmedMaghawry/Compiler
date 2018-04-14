cmake_minimum_required(VERSION 3.9)
project(compiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(compiler headers/Generator.h headers/Node.h headers/Transition.h classes/Generator.cpp classes/Node.cpp classes/Transition.cpp headers/DFA.h classes/DFA.cpp headers/NFA.h classes/NFA.cpp headers/Reader2.h headers/RegexParser.h classes/Reader2.cpp classes/RegexParser.cpp classes/Compiler.cpp classes/MinimizedDFA.cpp headers/MinimizedDFA.h headers/Construction.h headers/Evaluator.h headers/OperationHandler.h headers/PostfixInfix.h classes/Evaluator.cpp classes/OperationHandler.cpp classes/Construction.cpp classes/PostfixInfix.cpp)