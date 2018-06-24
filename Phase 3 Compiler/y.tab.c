
/*  A Bison parser, made from Bisi.y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	INT	258
#define	FLOAT	259
#define	BOOL	260
#define	IDENTIFIER	261
#define	ARITH_OP	262
#define	RELA_OP	263
#define	BOOL_OP	264
#define	IFW	265
#define	ELS	266
#define	WHL	267
#define	INTEGER	268
#define	FLT	269
#define	SECOL	270
#define	EQU	271
#define	LBrac	272
#define	RBrac	273
#define	LCur	274
#define	RCur	275

#line 1 "Bisi.y"

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

typedef enum {intT, fltT, boolT, voidT, errT} types;

void castingAdding(int start , int end, string operation);
bool isExist(string stri);
string operation_name(string op);
void backpatch(vector<int> *listy, int lableNum);
void EnterToCode(string x);
void output2File(void);
vector<int> * merge2Lists(vector<int> *list1, vector<int> *list2);
void writeLine(int num)
{
	EnterToCode(".line "+ to_string(num));
}

int while_begin;
extern int lines;
string outFile ;
int varNum = 1;
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

#line 58 "Bisi.y"
typedef union{
	struct {
		int exprType;
	} expr_type;
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
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		57
#define	YYFLAG		-32768
#define	YYNTBASE	21

#define YYTRANSLATE(x) ((unsigned)(x) <= 275 ? yytranslate[x] : 39)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     2,     6,     8,     9,    13,    15,    17,    19,
    21,    25,    27,    29,    30,    31,    32,    47,    48,    49,
    59,    64,    66,    68,    72,    74,    78,    80
};

static const short yyrhs[] = {    -1,
     0,    22,    24,    23,     0,    26,     0,     0,    26,    25,
    24,     0,    27,     0,    29,     0,    33,     0,    36,     0,
    28,     6,    15,     0,    13,     0,    14,     0,     0,     0,
     0,    10,    17,    38,    18,    19,    30,    24,    31,    20,
    11,    19,    32,    24,    20,     0,     0,     0,    34,    12,
    17,    38,    18,    19,    35,    24,    20,     0,     6,    16,
    37,    15,     0,     4,     0,     3,     0,    37,     7,    37,
     0,     6,     0,    17,    37,    18,     0,     5,     0,    37,
     8,    37,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   108,   122,   126,   131,   133,   140,   144,   147,   150,   153,
   157,   173,   176,   180,   191,   196,   203,   208,   214,   223,
   230,   258,   261,   264,   269,   291,   297,   314
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","INT","FLOAT",
"BOOL","IDENTIFIER","ARITH_OP","RELA_OP","BOOL_OP","IFW","ELS","WHL","INTEGER",
"FLT","SECOL","EQU","LBrac","RBrac","LCur","RCur","METHOD_BODY","@1","@2","STATEMENT_LIST",
"@3","STATEMENT","DECLARATION","PRIMITIVE_TYPE","IF","@4","@5","@6","WHILE",
"@7","@8","ASSIGNMENT","EXPRESSION","EXPR_BOOL", NULL
};
#endif

static const short yyr1[] = {     0,
    22,    23,    21,    24,    25,    24,    26,    26,    26,    26,
    27,    28,    28,    30,    31,    32,    29,    34,    35,    33,
    36,    37,    37,    37,    37,    37,    38,    38
};

static const short yyr2[] = {     0,
     0,     0,     3,     1,     0,     3,     1,     1,     1,     1,
     3,     1,     1,     0,     0,     0,    14,     0,     0,     9,
     4,     1,     1,     3,     1,     3,     1,     3
};

static const short yydefact[] = {     1,
    18,     0,     0,    12,    13,     2,     5,     7,     0,     8,
     9,     0,    10,     0,     0,     3,    18,     0,     0,    23,
    22,    25,     0,     0,    27,     0,     0,     6,    11,     0,
     0,     0,    21,     0,     0,     0,    26,    24,    28,    14,
     0,    18,    19,    15,    18,     0,     0,     0,    20,     0,
    16,    18,     0,    17,     0,     0,     0
};

static const short yydefgoto[] = {    55,
     1,    16,     6,    17,     7,     8,     9,    10,    42,    46,
    52,    11,    12,    45,    13,    26,    27
};

static const short yypact[] = {-32768,
    10,    -9,    -6,-32768,-32768,-32768,     2,-32768,     8,-32768,
-32768,    15,-32768,     9,     0,-32768,    10,    16,    17,-32768,
-32768,-32768,     9,    23,-32768,     1,    14,-32768,-32768,     0,
    11,     9,-32768,     9,    18,    21,-32768,    26,    26,-32768,
    22,    10,-32768,-32768,    10,    20,    24,    25,-32768,    27,
-32768,    10,    28,-32768,    42,    43,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,   -17,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   -13,    19
};


#define	YYLAST		49


static const short yytable[] = {    28,
    24,    -4,    20,    21,    25,    22,    14,    32,    34,    31,
    15,    20,    21,    18,    22,     2,    23,    32,    38,     3,
    39,    -4,     4,     5,    44,    23,    19,    47,    37,    32,
    29,    35,    32,    30,    53,    50,    40,    33,    41,    48,
    43,    56,    57,    49,     0,    51,     0,    54,    36
};

static const short yycheck[] = {    17,
    14,     0,     3,     4,     5,     6,    16,     7,     8,    23,
    17,     3,     4,     6,     6,     6,    17,     7,    32,    10,
    34,    20,    13,    14,    42,    17,    12,    45,    18,     7,
    15,    18,     7,    17,    52,    11,    19,    15,    18,    20,
    19,     0,     0,    20,    -1,    19,    -1,    20,    30
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/share/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 196 "/usr/local/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 109 "Bisi.y"
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
	;
    break;}
case 2:
#line 122 "Bisi.y"
{
	backpatch(yyvsp[0].statT.nextL,lblNum);
	EnterToCode("Lable"+ to_string(lblNum++) + ":");
	;
    break;}
case 3:
#line 126 "Bisi.y"
{
		EnterToCode("return");
		EnterToCode(".end method");
	;
    break;}
case 5:
#line 135 "Bisi.y"
{
	backpatch(yyvsp[0].statT.nextL,lblNum);
	EnterToCode("Lable"+ to_string(lblNum++) + ":");
	;
    break;}
case 6:
#line 140 "Bisi.y"
{
		yyval.statT.nextL = yyvsp[0].statT.nextL;
	;
    break;}
case 7:
#line 146 "Bisi.y"
{vector<int> * newVect = new vector<int>(); yyval.statT.nextL = newVect;;
    break;}
case 8:
#line 149 "Bisi.y"
{yyval.statT.nextL = yyvsp[0].statT.nextL;;
    break;}
case 9:
#line 152 "Bisi.y"
{yyval.statT.nextL = yyvsp[0].statT.nextL;;
    break;}
case 10:
#line 155 "Bisi.y"
{vector<int> * newVect = new vector<int>(); yyval.statT.nextL = newVect;;
    break;}
case 11:
#line 159 "Bisi.y"
{ 		string str(yyvsp[-1].idLex); 
			if(isExist(str))
			{
			yyerror("Invalid Variable");
			}else{ 
			if(yyvsp[-2].exprType == intT){
  			EnterToCode("iconst_0\nistore " + to_string(varNum));
 			}else if (yyvsp[-2].exprType == fltT){
 			EnterToCode("fconst_0\nfstore " + to_string(varNum));
 			}
 			symbs[str] = make_pair(varNum++,(types)yyvsp[-2].exprType);
 		 	}
	;
    break;}
case 12:
#line 175 "Bisi.y"
{yyval.exprType = intT;;
    break;}
case 13:
#line 178 "Bisi.y"
{yyval.exprType = fltT;;
    break;}
case 14:
#line 186 "Bisi.y"
{
	backpatch(yyvsp[-2].EXPR_BOOL_val.trueL,lblNum);
	EnterToCode("Lable"+ to_string(lblNum++)+ ":");
	;
    break;}
case 15:
#line 191 "Bisi.y"
{
	yyval.statT.nextL->push_back(outCode.size());
	EnterToCode("goto ");
	;
    break;}
case 16:
#line 198 "Bisi.y"
{
	backpatch(yyvsp[-8].EXPR_BOOL_val.falseL,lblNum);
	EnterToCode("Lable"+ to_string(lblNum++) + ":");
	;
    break;}
case 17:
#line 204 "Bisi.y"
{
		yyval.statT.nextL = merge2Lists(yyvsp[-7].statT.nextL, yyvsp[-1].statT.nextL);
	;
    break;}
case 18:
#line 209 "Bisi.y"
{
	while_begin = lblNum;
	EnterToCode("Lable"+ to_string(lblNum++) + ":");
	;
    break;}
case 19:
#line 218 "Bisi.y"
{
	backpatch(yyvsp[-2].EXPR_BOOL_val.trueL,lblNum);
	EnterToCode("Lable"+ to_string(lblNum++) + ":");
	;
    break;}
case 20:
#line 224 "Bisi.y"
{
		EnterToCode("goto Lable"+to_string(while_begin));
		backpatch(yyvsp[-1].statT.nextL,while_begin);
		yyval.statT.nextL = yyvsp[-5].EXPR_BOOL_val.falseL;
	;
    break;}
case 21:
#line 235 "Bisi.y"
{
		string str(yyvsp[-3].idLex);
		if(isExist(str))
		{
			if(yyvsp[-1].expr_type.exprType == symbs[str].second)
			{
				if(yyvsp[-1].expr_type.exprType == intT)
				{
					EnterToCode("istore " + to_string(symbs[str].first));
				}else if (yyvsp[-1].expr_type.exprType == fltT)
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
	;
    break;}
case 22:
#line 260 "Bisi.y"
{yyval.expr_type.exprType = fltT; EnterToCode("ldc "+to_string(yyvsp[0].floatV));;
    break;}
case 23:
#line 263 "Bisi.y"
{yyval.expr_type.exprType = intT;  EnterToCode("ldc "+to_string(yyvsp[0].intV));;
    break;}
case 24:
#line 268 "Bisi.y"
{castingAdding(yyvsp[-2].expr_type.exprType, yyvsp[0].expr_type.exprType, string(yyvsp[-1].opV));;
    break;}
case 25:
#line 271 "Bisi.y"
{
		string str(yyvsp[0].idLex);
		if(isExist(str))
		{
			yyval.expr_type.exprType = symbs[str].second;
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
			yyval.expr_type.exprType = errT;
		}
	;
    break;}
case 26:
#line 295 "Bisi.y"
{yyval.expr_type.exprType = yyvsp[-1].expr_type.exprType;;
    break;}
case 27:
#line 299 "Bisi.y"
{
		if(yyvsp[0].booleanV)
		{
			yyval.EXPR_BOOL_val.trueL = new vector<int> ();
			yyval.EXPR_BOOL_val.falseL = new vector<int>();
			yyval.EXPR_BOOL_val.trueL->push_back(outCode.size());
			EnterToCode("goto ");
		}else
		{
			yyval.EXPR_BOOL_val.trueL = new vector<int> ();
			yyval.EXPR_BOOL_val.falseL= new vector<int>();
			yyval.EXPR_BOOL_val.falseL->push_back(outCode.size());
			EnterToCode("goto ");
		}
	;
    break;}
case 28:
#line 318 "Bisi.y"
{
		string op (yyvsp[-1].opV);
		yyval.EXPR_BOOL_val.trueL = new vector<int>();
		yyval.EXPR_BOOL_val.trueL ->push_back (outCode.size());
		yyval.EXPR_BOOL_val.falseL = new vector<int>();
		yyval.EXPR_BOOL_val.falseL->push_back(outCode.size()+1);
		EnterToCode(operation_name(op)+ " ");
		EnterToCode("goto ");
	;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 498 "/usr/local/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 328 "Bisi.y"


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
