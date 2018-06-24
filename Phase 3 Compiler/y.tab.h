#include<vector>
		using namespace std;
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


extern YYSTYPE yylval;
