%{
#include <cstdio>
#include <string.h>
#include "visitor.h"
using namespace std;
int yylex(void);
void yyerror (char const *);
ProgramASTnode * rootnode;
%}
%union{
	int val;
	char * str;
	char ch;

	class LitExprASTnode * literal;
	class IdASTnode * id_list;
	class VarlistASTnode * var_names;
	class FielddeclASTnode * field_decl;
	class FielddecllistASTnode * field_decl_list;
	class ProgramASTnode * program;
	class IdlistASTnode * var_list;
	class VardeclASTnode * var_decl;
	class VardecllistASTnode * var_decl_list;
	class StatementASTnode * statement;
	class StatementlistASTnode * statement_list;
	class BlockstatementASTnode * block;
	class LocationASTnode * location;
	class MethodASTnode * method_call;
	class MethodArgsASTNode * method_args;
	class CalloutargASTnode * callout_arg;
	class CalloutArgsASTnode * callout_args_list;
	class IdtypelistASTnode * arg_list;
	class MethoddeclASTnode * method_decl;
	class MethoddecllistASTnode * method_decl_list;
	class ExprASTnode * expr;
	class BinaryExprASTnode * binaryexpr;

}
/* declare tokens */
%define parse.error verbose
%type <program> program
%type <literal> literal
%type <id_list> id_list
%type <var_names> var_names
%type <field_decl> field_decl
%type <field_decl_list> field_decl_list
%type <var_list> var_list;
%type <var_decl> var_decl;
%type <var_decl_list> var_decl_list;
%type <statement> statement;
%type <statement_list> statement_list;
%type <block> block;
%type <location> location;
%type <method_call> method_call;
%type <method_args> method_args;
%type <str> method_name;
%type <str> assign_op;
%type <callout_arg> callout_arg;
%type <callout_args_list> callout_args_list;
%type <arg_list> arg_list;
%type <method_decl> method_decl;
%type <method_decl_list> method_decl_list;
%type <expr> expr;
%type <binaryexpr> arith_expr;
%type <binaryexpr> rel_expr;
%type <binaryexpr> eq_expr;
%type <binaryexpr> cond_expr;
%token PROGRAM
%token CLASS CALLOUT BREAK IF ELSE FOR RETURN CONTINUE
%token<str> DATA_TYPE BOOL_LITERAL VOID
%token<ch> CHAR_LITERAL
%token<val> INTEGER_LITERAL
%token<str> STRING ID
%token OB CB COB CCB SOB SCB
%token<str> ADD SUB MUL DIV MOD NOT
%token<str> LT GT LTEQ GTEQ EQ EQEQ NEQ PLUSEQ MINUSEQ
%token<str> AND OR
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
		{ $$ = new ProgramASTnode($4, $5); rootnode = $$; printf("Program Parsed successfully");}
		| CLASS PROGRAM COB field_decl_list CCB
		{ $$ = new ProgramASTnode($4); rootnode = $$; printf("Program Parsed successfully");}
;
//field_decl_list : field_decl field_decl_list (not working)
field_decl_list : field_decl_list field_decl { $$->push_fielddecl($2); }
		| %empty { $$ = new FielddecllistASTnode(); }
		;
field_decl : DATA_TYPE var_names SEMICOLON { $$ = new FielddeclASTnode(string($1), $2); }
	   ;
var_names : id_list { $$ = new VarlistASTnode(); $$->push_varname($1); }
	  | var_names COMMA id_list { $$->push_varname($3); }
	  ;
id_list : ID { $$ = new IdASTnode(string($1)); }
	| ID SOB INTEGER_LITERAL SCB { $$ = new IdASTnode(string($1), $3); }
	;
//method_decl_list : method_decl_list method_decl (not working)
method_decl_list : method_decl_list method_decl { $1->push_methoddecl($2); $$ = $1; }
		 | method_decl { $$ = new MethoddecllistASTnode(); $$->push_methoddecl($1); }
		 ;
method_decl : DATA_TYPE ID OB arg_list CB block { $$ = new MethoddeclASTnode(string($1), $2, $4, $6); }
	    | VOID ID OB arg_list CB block { $$ = new MethoddeclASTnode(string($1), $2, $4, $6); }
	    ;
arg_list : DATA_TYPE ID { $$ = new IdtypelistASTnode() ; $$->push_idtype(new IdtypeASTnode(string($1),$2)); }
	 | arg_list COMMA  DATA_TYPE ID { $1->push_idtype(new IdtypeASTnode(string($3),$4)); $$ = $1;}
	 //| %empty
	 ;
block : COB var_decl_list statement_list CCB { $$ = new BlockstatementASTnode($2, $3); }
      ;
var_decl_list : var_decl SEMICOLON var_decl_list { $$->push_vardecl($1); }
	      | %empty { $$ = new VardecllistASTnode(); }
	      ;
var_decl : DATA_TYPE var_list {$$ = new VardeclASTnode(string($1), $2); }
	 ;
var_list : ID { $$ = new IdlistASTnode(); $$->push_id(new IdASTnode(string($1))); }
	 | var_list COMMA ID { $1->push_id(new IdASTnode(string($3))); $$ = $1;}
	 ;
statement_list : statement_list statement { $1-> push_statement($2); $$ = $1; }
	       | %empty { $$ =  new StatementlistASTnode(); }
	       ;
statement : location assign_op expr SEMICOLON { $$ = new AssignstatementASTnode($1, string($2), $3); }
	  | method_call SEMICOLON { $$ = $1; }
	  | IF OB expr CB block { $$ = new IfelseASTnode($5, $3, NULL); }
	  | IF OB expr CB block ELSE block { $$ = new IfelseASTnode($5, $3, $7); }
	  | FOR ID EQ expr COMMA expr block { $$ = new ForstatementASTnode(string($2), $4, $6, $7); }
	  | RETURN SEMICOLON { $$ = new ReturnstatementASTnode(NULL); }
	  | RETURN expr SEMICOLON { $$ = new ReturnstatementASTnode($2); }
	  | BREAK SEMICOLON { $$ = new BreakstatementASTnode(); }
	  | CONTINUE SEMICOLON { $$ = new ContinuestatementASTnode(); }
	  | block { $$ = $1; }
	  ;
location : ID { $$ = new LocationASTnode(string($1), NULL);}
	 | ID SOB expr SCB { $$ = new LocationASTnode(string($1), $3);}
	 ;
assign_op : EQ
	  | PLUSEQ
	  | MINUSEQ
	  ;
method_call : method_name OB method_args CB { $$ = new DefinedMethodASTnode(string($1), $3); }
	    | CALLOUT OB STRING COMMA callout_args_list CB { $$ = new CalloutMethodASTnode(string($3), $5);}
	    ;
method_name : ID
	    ;
method_args : expr { $$->push_argument($1); }
	    | method_args COMMA expr { $1->push_argument($3); $$ = $1;}
	    | %empty { $$ = new MethodArgsASTNode();}
	    ;
callout_args_list : callout_arg { $$ = new CalloutArgsASTnode(); $$->push_argument($1);}
	    | callout_args_list COMMA callout_arg { $1->push_argument($3); $$ = $1; }
	    ;
callout_arg : expr { $$ = new ExprargASTnode($1); }
	    | STRING {$$ = new StringargASTnode(string($1)); }
	    ;
//expr : expr ADD expr   { $$ = new BinaryExprASTnode($1, $3, "+"); }
expr : location { $$ = $1;}
     | method_call { $$ = $1;}
     | literal { $$ = $1; }
     | arith_expr { $$ = $1;}
     | rel_expr { $$ = $1;}
     | eq_expr { $$ = $1;}
     | cond_expr { $$ = $1;}
     | SUB expr %prec UMINUS { $$ = new UnaryExprASTnode($2, string($1)); }
     | NOT expr %prec NOT { $$ = new UnaryExprASTnode($2, string($1)); }
     | OB expr CB {$$ = $2;}
     ;
arith_expr : expr ADD expr  { $$ = new BinaryExprASTnode($1, $3, string($2)); }
           | expr SUB expr  { $$ = new BinaryExprASTnode($1, $3, string($2)); }
           | expr MOD expr  { $$ = new BinaryExprASTnode($1, $3, string($2)); }
           | expr MUL expr  { $$ = new BinaryExprASTnode($1, $3, string($2)); }
           | expr DIV expr  { $$ = new BinaryExprASTnode($1, $3, string($2)); }
           ;
rel_expr : expr LT expr { $$ = new BinaryExprASTnode($1, $3, string($2)); }
	 | expr GT expr { $$ = new BinaryExprASTnode($1, $3, string($2)); }
	 | expr LTEQ expr { $$ = new BinaryExprASTnode($1, $3, string($2)); }
	 | expr GTEQ expr { $$ = new BinaryExprASTnode($1, $3, string($2)); }
	 ;
eq_expr : expr EQEQ expr { $$ = new BinaryExprASTnode($1, $3, string($2)); }
	| expr NEQ expr { $$ = new BinaryExprASTnode($1, $3, string($2)); }
	;
cond_expr : expr AND expr { $$ = new BinaryExprASTnode($1, $3, string($2)); }
	  | expr OR expr { $$ = new BinaryExprASTnode($1, $3, string($2)); }
	  ;
literal : INTEGER_LITERAL { $$ = new IntLitExprASTnode($1); }
	| CHAR_LITERAL { $$ = new CharLitExprASTnode($1); }
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
