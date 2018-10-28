%{
#include <stdio.h>
#include "visitor.h"
using namespace std;
int yylex(void);
void yyerror (char const *);
ProgramASTnode * rootnode;
%}
%union{
	int val;
	char * str;
	class BinaryExprASTnode * astnode;
	class LitExprASTnode * literal;
	class IdASTnode * id_list;
	class VarlistASTnode * var_names;
	class FieldDeclASTnode * field_decl;
	class FieldDecllistASTnode * field_decl_list;
	class ProgramASTnode * program;
}
/* declare tokens */
%define parse.error verbose
%type<program>program
%type <astnode> expr
%type <literal> literal
%type <id_list> id_list
%type <var_names> var_names
%type <field_decl> field_decl
%type <field_decl_list> field_decl_list
%token PROGRAM
%token CLASS CALLOUT BREAK IF ELSE FOR RETURN VOID CONTINUE
%token<str> DATA_TYPE BOOL_LITERAL CHAR_LITERAL
%token<val> INTEGER_LITERAL
%token<str> STRING ID
%token OB CB COB CCB SOB SCB
%token ADD SUB MUL DIV MOD NOT
%token LT GT LTEQ GTEQ EQ EQEQ NEQ PLUSEQ MINUSEQ
%token AND OR
%token SEMICOLON COMMA

// increasing order of precedence http://www.difranco.net/compsci/C_Operator_Precedence_Table.htm
%left OR
%left AND
%left EQEQ NEQ
%left LT GT LTEQ GTEQ
%left ADD SUB
%left MUL DIV MOD
%precedence NOT UMINUS

%%
program : CLASS PROGRAM COB field_decl_list method_decl_list CCB 
	{ $$ = new ProgramASTnode($4); rootnode = $$; printf("Program Parsed successfully");}
;
//field_decl_list : field_decl field_decl_list (not working)
field_decl_list : field_decl_list field_decl { $$->push_fielddecl($2); }
		| %empty { $$ = new FieldDecllistASTnode(); }
		;
field_decl : DATA_TYPE var_names SEMICOLON { $$ = new FieldDeclASTnode(string($1), $2); }
	   ;
var_names : id_list { $$ = new VarlistASTnode(); $$->push_varname($1); }
	  | var_names COMMA id_list { $$->push_varname($3); }
	  ;
id_list : ID { $$ = new IdASTnode(string($1)); }
	| ID SOB INTEGER_LITERAL SCB { $$ = new IdASTnode(string($1), $3); }
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
block : COB var_decl_list statement_list CCB
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
callout_arg : expr 
	    | STRING
	    ;
//expr : expr ADD expr   { $$ = new BinaryExprASTnode($1, $3, "+"); }
expr : location
     | method_call
     | literal
     | arith_expr
     | rel_expr
     | eq_expr
     | cond_expr
     | SUB expr %prec UMINUS
     | NOT expr %prec NOT
     | OB expr CB
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
literal : INTEGER_LITERAL { $$ = new IntLitExprASTnode($1); }
	| CHAR_LITERAL { $$ = new CharLitExprASTnode('a'); }
	| BOOL_LITERAL { $$ = new BoolLitExprASTnode($1); }
	;
%%
int main(int argc, char **argv)
{
  yyparse();
  printf("\nParsing Completed\n");
  class visitor v;
  rootnode->accept(v);
  return 0;
}

void yyerror(char const *s)
{
  fprintf(stderr, "error: %s\n", s);
}
