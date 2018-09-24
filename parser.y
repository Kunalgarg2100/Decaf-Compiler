%{
#include <stdio.h>
int yylex(void);
void yyerror (char const *);
%}

/* declare tokens */
%token PROGRAM
%token CLASS CALLOUT BREAK IF ELSE FOR RETURN VOID CONTINUE
%token DATA_TYPE BOOL_LITERAL INTEGER_LITERAL CHAR_LITERAL
%token STRING IDENTIFER
%token OB CB COB CCB SOB SCB
%token ADD SUB MUL DIV PER NOT
%token LT GT LTEQ GTEQ EQ EQEQ NEQ
%token AND OR EOL
%%
calclist: /* nothing */                       
	 | calclist expr EOL { printf("= %d\n", $2); } 
;
expr : literal
	| expr bin_op expr
;
bin_op : arith_op
	| rel_op
	| eq_op
	| cond_op
;
arith_op : ADD
	| SUB
	| MUL
	| DIV
	| PER
;
rel_op : LT
	| GT
	| LTEQ
	| GTEQ
;
eq_op : EQEQ
	| NEQ
;
cond_op : AND
	| OR
;
literal : INTEGER_LITERAL 
	| CHAR_LITERAL 
	| BOOL_LITERAL
;



%%
int main(int argc, char **argv)
{
  yyparse();
  return 0;
}

void yyerror(char const *s)
{
  fprintf(stderr, "error: %s\n", s);
}
