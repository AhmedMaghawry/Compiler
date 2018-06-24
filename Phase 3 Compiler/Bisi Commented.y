%{
#include <cstring>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <map>
#include <unistd.h>

using namespace std;
#define GetCurrentDir getcwd

extern  int yylex();
extern  FILE *yyin;
void yyerror(const char * s);

ofstream fout("out.j");
/*
The types of Exprestions and primative types
To be checked for parsing and casting
*/
typedef enum {intT, fltT, boolT, voidT, errT} types;
/*
Cast the Expresion variables by adding 'i' of 'f' before the command to indicates its type
*/
void castingAdding(int start , int end, string operation);
/*
check if the current symbole is exsist before or not
*/
bool isExist(string stri);
/*
Pares the operation symbole to its equivelant name
*/
string operation_name(string op);
/*
Doing the backbatch by adding the lable number to its place by :
- Getting the list which contain the locations of the requried places to fill
- and the lable number to fill with which calculated by its order in the lables 
by the increasing variable lblNum
*/
void backpatch(vector<int> *listy, int lableNum);
/*
Add the Code to the list of Codes
*/
void EnterToCode(string x);
/*
Print the code to the File
*/
void output2File(void);
/*
Merge 2 lists because of 
2 Production in the right side and have the same name
*/
vector<int> * merge2Lists(vector<int> *list1, vector<int> *list2);
void writeLine(int num)
{
	EnterToCode(".line "+ to_string(num));
}

/*
Used to save the lable number of the first production in WHILE production
*/
int while_begin;
/*
Number of Lines in code 
- it is extern because it used in lex and increased by the number of \n
*/
extern int lines;
string outFile ;
/*
To differ the variables
*/
int varNum = 1;
/*
Counter on the the lables numbers to differ them and backbatch
*/
int lblNum = 0;
map<string,string> tokMean = {
	{"+", "add"},
	{"-", "sub"},
	{"/", "div"},
	{"*", "mul"},
	{"&", "and"},
	{"|", "or"},
	{">",  "if_icmpgt"},
	{"<",  "if_icmplt"},
	{"==", "if_icmpeq"},
	{"<=", "if_icmple"},
	{">=", "if_icmpge"},
	{"!=", "if_icmpne"}
};
map<string, pair<int,types> > symbs;
vector<string> outCode;
%}

%start METHOD_BODY

%union{
	/*
	The attribute of the PRIMITIVE_TYPE and EXPRESSION to express the type of the exression
	*/
	struct {
		int exprType;
	} expr_type;
	/*
	To Express the boolean expression in the While or IF 
	*/
	struct {
		vector<int> *trueL;
		vector<int> *falseL;
	} EXPR_BOOL_val;
	struct {
		vector<int> *nextL;
	} statT;
	int intV;
	float floatV;
	int booleanV;
	char * idLex;
	char * opV;
	int exprType;
}

%token <intV> INT
%token <floatV> FLOAT
%token <booleanV> BOOL
%token <idLex> IDENTIFIER
%token <opV> ARITH_OP
%token <opV> RELA_OP
%token <opV> BOOL_OP

%token IFW
%token ELS
%token WHL
%token INTEGER
%token FLT
%token SECOL
%token EQU
%token LBrac
%token RBrac
%token LCur
%token RCur


%type <exprType> PRIMITIVE_TYPE
%type <expr_type> EXPRESSION
%type <EXPR_BOOL_val> EXPR_BOOL
%type <statT> STATEMENT
%type <statT> STATEMENT_LIST
%type <statT> IF
%type <statT> WHILE


%% 
METHOD_BODY: 
	{
	EnterToCode(".source " + outFile);
	EnterToCode(".class public test\n.super java/lang/Object\n");
	EnterToCode(".method public <init>()V");
	EnterToCode("aload_0");
	EnterToCode("invokenonvirtual java/lang/Object/<init>()V");
	EnterToCode("return");
	EnterToCode(".end method\n");
	EnterToCode(".method public static main([Ljava/lang/String;)V");
	EnterToCode(".limit locals 100\n.limit stack 100");
	EnterToCode(".line 1"); 
	}
	STATEMENT_LIST
	{
	backpatch($2.nextL,lblNum);
	EnterToCode("Lable"+ to_string(lblNum++) + ":");
	}
	{
		EnterToCode("return");
		EnterToCode(".end method");
	}
	;
STATEMENT_LIST: 
	 STATEMENT 
	| 
	STATEMENT
	{
	backpatch($1.nextL,lblNum);
	EnterToCode("Lable"+ to_string(lblNum++) + ":");
	}
	STATEMENT_LIST 
	{
		$$.nextL = $3.nextL;
	}
	;
STATEMENT: 
	DECLARATION
	{vector<int> * newVect = new vector<int>(); $$.nextL = newVect;}
	|
	IF
	{$$.nextL = $1.nextL;}
	|
	WHILE
	{$$.nextL = $1.nextL;}
	|
	ASSIGNMENT
	{vector<int> * newVect = new vector<int>(); $$.nextL = newVect;}
	;
DECLARATION: 
	PRIMITIVE_TYPE IDENTIFIER SECOL
	{ 		string str($2); 
			if(isExist(str))
			{
			yyerror("Invalid Variable");
			}else{ 
			if($1 == intT){
  			EnterToCode("iconst_0\nistore " + to_string(varNum));
 			}else if ($1 == fltT){
 			EnterToCode("fconst_0\nfstore " + to_string(varNum));
 			}
 			symbs[str] = make_pair(varNum++,(types)$1);
 		 	}
	}
	;
PRIMITIVE_TYPE: 
	INTEGER
	{$$ = intT;}
	|
	FLT
	{$$ = fltT;}
	;
IF: 
	IFW
	LBrac 
	EXPR_BOOL 
	RBrac
	LCur 
	{
	backpatch($3.trueL,lblNum);
	EnterToCode("Lable"+ to_string(lblNum++)+ ":");
	}
	STATEMENT_LIST
	{
	$$.nextL->push_back(outCode.size());
	EnterToCode("goto ");
	}
	RCur 
	ELS
	LCur 
	{
	backpatch($3.falseL,lblNum);
	EnterToCode("Lable"+ to_string(lblNum++) + ":");
	}
	STATEMENT_LIST 
	RCur
	{
		$$.nextL = merge2Lists($7.nextL, $13.nextL);
	}
	;
WHILE:
	{
	while_begin = lblNum;
	EnterToCode("Lable"+ to_string(lblNum++) + ":");
	}
	WHL
	LBrac
	EXPR_BOOL
	RBrac
	LCur 
	{
	backpatch($4.trueL,lblNum);
	EnterToCode("Lable"+ to_string(lblNum++) + ":");
	}
	STATEMENT_LIST
	RCur
	{
		EnterToCode("goto Lable"+to_string(while_begin));
		backpatch($8.nextL,while_begin);
		$$.nextL = $4.falseL;
	}
	;
ASSIGNMENT: 
	IDENTIFIER
	EQU
	EXPRESSION
	SECOL
	{
		string str($1);
		if(isExist(str))
		{
			if($3.exprType == symbs[str].second)
			{
				if($3.exprType == intT)
				{
					EnterToCode("istore " + to_string(symbs[str].first));
				}else if ($3.exprType == fltT)
				{
					EnterToCode("fstore " + to_string(symbs[str].first));
				}
			}
			else
			{
				yyerror("Error");
			}
		}else{
			yyerror("Error");
		}
	}
	;
EXPRESSION: 
	FLOAT
	{$$.exprType = fltT; EnterToCode("ldc "+to_string($1));}
	|
	INT
	{$$.exprType = intT;  EnterToCode("ldc "+to_string($1));} 
	|
	EXPRESSION
	ARITH_OP
	EXPRESSION
	{castingAdding($1.exprType, $3.exprType, string($2));}
	|
	IDENTIFIER
	{
		string str($1);
		if(isExist(str))
		{
			$$.exprType = symbs[str].second;
			if(symbs[str].second == intT)
			{
				EnterToCode("iload " + to_string(symbs[str].first));
			}else if (symbs[str].second == fltT)
			{
				EnterToCode("fload " + to_string(symbs[str].first));
			}
		}
		else
		{
			string err = "identifier: "+str+" isn't declared in this scope";
			yyerror(err.c_str());
			$$.exprType = errT;
		}
	}
	|
	LBrac
	EXPRESSION
	RBrac
	{$$.exprType = $2.exprType;}
	;
EXPR_BOOL:
	BOOL
	{
		if($1)
		{
			$$.trueL = new vector<int> ();
			$$.falseL = new vector<int>();
			$$.trueL->push_back(outCode.size());
			EnterToCode("goto ");
		}else
		{
			$$.trueL = new vector<int> ();
			$$.falseL= new vector<int>();
			$$.falseL->push_back(outCode.size());
			EnterToCode("goto ");
		}
	}	
	|
	EXPRESSION
	RELA_OP
	EXPRESSION		
	{
		string op ($2);
		$$.trueL = new vector<int>();
		$$.trueL ->push_back (outCode.size());
		$$.falseL = new vector<int>();
		$$.falseL->push_back(outCode.size()+1);
		EnterToCode(operation_name(op)+ " ");
		EnterToCode("goto ");
	}
	;
%%

main (int argv, char * argc[])
{
	FILE *file;
	if(argv == 1) 
	{
		file = fopen("code.txt", "r");
		outFile = "code.txt";
	}
	else 
	{
		file = fopen(argc[1], "r");
		outFile = string(argc[1]);
	}
	if (!file) {
		printf("Error Open File\n");
		return -1;
	}
	yyin = file;
	yyparse();
	output2File();
}

void yyerror(const char * s)
{
	printf("error@%d: %s\n",lines, s);
}


void castingAdding(int start , int end, string operation)
{
	if(start == end)
	{
		if(start == intT)
		{
			EnterToCode("i" + operation_name(operation));
		}else if (start == fltT)
		{
			EnterToCode("f" + operation_name(operation));
		}
	}
}

string operation_name(string op)
{
	if(tokMean.find(op) != tokMean.end())
	{
		return tokMean[op];
	}
	return "";
}

bool isExist(string stri)
{
	return (symbs.find(stri) != symbs.end());
}

void backpatch(vector<int> *listy, int lableNum)
{
	if(listy)
	for(int i =0 ; i < listy->size() ; i++)
	{
		outCode[(*listy)[i]] = outCode[(*listy)[i]] + "Lable"+to_string(lableNum);
	}
}

vector<int> * merge2Lists(vector<int> *list1, vector<int> *list2)
{
	if(list1 && list2){
		vector<int> *list = new vector<int> (*list1);
		list->insert(list->end(), list2->begin(),list2->end());
		return list;
	}else if(list1)
	{
		return list1;
	}else if (list2)
	{
		return list2;
	}else
	{
		return new vector<int>();
	}
}

void EnterToCode(string x)
{
	outCode.push_back(x);
}

void output2File(void)
{
	for ( int i = 0 ; i < outCode.size() ; i++)
	{
		fout<<outCode[i]<<endl;
	}
}
