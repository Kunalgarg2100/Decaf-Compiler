%{
#include <stdio.h>
int yylex(void);
void yyerror (char const *);
%}

/* declare tokens */
%define parse.error verbose
%token PROGRAM
%token CLASS CALLOUT BREAK IF ELSE FOR RETURN VOID CONTINUE
%token DATA_TYPE BOOL_LITERAL INTEGER_LITERAL CHAR_LITERAL
%token STRING ID
%token OB CB COB CCB SOB SCB
%token ADD SUB MUL DIV MOD NOT
%token LT GT LTEQ GTEQ EQ EQEQ NEQ PLUSEQ MINUSEQ
%token AND OR EOL
%token SEMICOLON COMMA

// increasing order of precedence http://www.difranco.net/compsci/C_Operator_Precedence_Table.htm
%left OR
%left AND
%left EQEQ NEQ
%left LT GT LTEQ GTEQ
%left ADD SUB
%left MUL DIV MOD


%%
/*calclist:                        
	| calclist expr EOL { printf("= %d\n", $2); } 
;*/
program : CLASS PROGRAM COB field_decl_list method_decl_list CCB
	{ printf("Program started");}
;
//field_decl_list : field_decl field_decl_list (not working)
field_decl_list : field_decl_list field_decl 
		| %empty
		;
field_decl : DATA_TYPE var_names SEMICOLON
	   ;
var_names : id_list
	  | var_names COMMA id_list
	  ;
id_list : ID
	| ID SOB INTEGER_LITERAL SCB
	;
//method_decl_list : method_decl_list method_decl (not working)
method_decl_list : method_decl method_decl_list
		 | %empty
		 ;
method_decl : DATA_TYPE ID OB arg_list CB block
	    | VOID ID OB arg_list CB block
	    ;
arg_list : DATA_TYPE ID
	 | arg_list COMMA DATA_TYPE ID
	 | %empty
	 ;
block : OB var_decl_list statement_list CB
      ;
var_decl_list : var_decl SEMICOLON var_decl_list
	      | %empty
	      ;
var_decl : DATA_TYPE var_list
	 ;
var_list : ID
	 | var_list COMMA ID
	 ;
statement_list : statement statement_list
	       | %empty
	       ;
statement : location assign_op expr SEMICOLON
	  | method_call SEMICOLON
	  | IF OB expr CB block
	  | IF OB expr CB block ELSE block
	  | FOR ID EQ expr COMMA expr block
	  | RETURN SEMICOLON
	  | RETURN expr SEMICOLON
	  | BREAK SEMICOLON
	  | CONTINUE SEMICOLON
	  | block
	  ;
location : ID
	 | ID SOB expr SCB
	 ;
assign_op : EQ
	  | PLUSEQ
	  | MINUSEQ
	  ;
method_call : method_name OB method_args CB
	    | CALLOUT OB STRING callout_args_list CB
	    ;
method_name : ID
	    ;
method_args : expr
	    | method_args COMMA expr
	    | %empty
	    ;
callout_args_list : COMMA callout_args
		  | %empty
		  ;
callout_args : callout_arg
	     | callout_args COMMA callout_arg
	     ;
//callout_arg : expr | INTEGER_LITERAL as expr already includes INTEGER_LITERAL
callout_arg : expr
	    ;
expr : ID SOB expr SCB //location
     | method_call
     | literal
     | arith_expr
     | rel_expr
     | eq_expr
     | cond_expr
     ;
arith_expr : expr ADD expr
	   | expr SUB expr 
	   | expr MOD expr
	   | expr MUL expr
	   | expr DIV expr 
	   ;
rel_expr : expr LT expr
	 | expr GT expr
	 | expr LTEQ expr
	 | expr GTEQ expr
	 ;
eq_expr : expr EQEQ expr
	| expr NEQ expr
	;
cond_expr : expr AND expr
	  | expr OR expr
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
