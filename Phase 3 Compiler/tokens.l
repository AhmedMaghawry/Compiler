%{
	#include "y.tab.h"
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	int lines = 1;
%}

letter  [a-zA-Z]
digit [0-9]
digits {digit}+

id {letter}({letter}|{digit})*
num "-"?{digits}
fnum "-"?{digits}.{digits}("E"{digits}+)?
relop "=="|"!="|">"|">="|"<"|"<="
boolop "&&"|"||"
op "+"|"-"|"*"|"/"|"%"|"&"|"|"
binary "true"|"false"

%%
"if"	{return IFW;}
"else"	{return ELS;}
"while"	{return WHL;}
"int"	{return INTEGER;}
"float"	{return FLT;}
{op}	{yylval.opV = strdup(yytext); return ARITH_OP;}
{num}	{yylval.intV = atoi(yytext); return INT;}
{fnum}	{yylval.floatV = atof(yytext); return FLOAT;}
{relop} {yylval.opV = strdup(yytext); return RELA_OP;}
{boolop} {yylval.opV = strdup(yytext); return BOOL_OP;}
{binary} {if(!strcmp(yytext,"true")){ yylval.booleanV = 1;} else { yylval.booleanV = 0;} return BOOL;}
{id}	{yylval.idLex = strdup(yytext);return IDENTIFIER;}
";" { return SECOL;}
"=" {return EQU;}
"(" { return LBrac;}
")" {return RBrac;}
"{" {return LCur;}
"}" {return RCur;}
\n	{++lines;}
%%
int yywrap() {
   return -1;
}
