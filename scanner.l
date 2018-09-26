/* recognize tokens for the calculator and print them out */
%{
    #include<stdio.h>
    #include<stdlib.h>
   enum yytokentype {
     INTEGER_LITERAL = 258,
     ADD = 259,
     SUB = 260,
     MUL = 261,
     DIV = 262,
     OB = 264,
     CB = 265,
     COB = 266,
     CCB = 267,
     SOB = 268,
     SCB = 269,
     EOL = 270,
     PROGRAM = 271,
     CLASS = 272,
     CALLOUT = 273,
     BREAK = 274,
     IF = 275,
     ELSE = 276,
     DATA_TYPE = 277,
     CONTINUE = 278,
     RETURN = 279,
     BOOL_LITERAL = 280,
     FOR = 281,
     VOID = 282,
     EQ = 283,
     EQEQ = 284,
     LT = 285,
     LTEQ = 286,
     GT = 287,
     GTEQ = 288,
     CHAR_LITERAL = 289,
     STRING = 290,
     IDENTIFER = 291,
     PER = 292,
     NOT = 293,
     NEQ = 294,
     AND = 295,
     OR = 296,
     SEMICOLON = 297,
     COMMA = 298
    };
    int  yylval;
%}
digit [0-9]
letter [a-zA-Z]
alpha {letter}|[_]
alpha_num {alpha}|{digit}
hex_digit {digit}|[a-fA-F]
char (\\.|[^'\\\n])
string (\\.|[^"])*
%%
"Program" { fprintf(stdout,"PROGRAM\n"); return PROGRAM; }
"class" { fprintf(stdout,"CLASS\n"); return CLASS; }
"callout" { fprintf(stdout,"CALLOUT\n"); return CALLOUT; }
"break" { fprintf(stdout,"BREAK\n"); return BREAK; }
"if" { fprintf(stdout,"IF\n"); return IF; }
"else" { fprintf(stdout,"ELSE\n"); return ELSE; }
"for" { fprintf(stdout,"FOR\n"); return FOR; }
"return" { fprintf(stdout,"RETURN\n"); return RETURN; }
"void" { fprintf(stdout,"VOID\n"); return VOID; }
"continue" { fprintf(stdout,"CONTINUE\n"); return CONTINUE; }
"int"|"boolean" { fprintf(stdout,"DATA_TYPE:%s\n",yytext); return DATA_TYPE; }
"true"|"false" { fprintf(stdout,"BOOL_LITERAL:%s\n",yytext); return BOOL_LITERAL; }
{digit}+|"0x"{hex_digit}+ { fprintf(stdout,"INTEGER_LITERAL:%s\n",yytext); return INTEGER_LITERAL; }
'{char}'  { fprintf(stdout,"CHAR_LITERAL:%s\n",yytext); return CHAR_LITERAL; }
\"{string}\"  { fprintf(stdout,"STRING:%s\n",yytext); return STRING; }
{alpha}+{alpha_num}* { fprintf(stdout,"IDENTIFER:%s\n",yytext); return IDENTIFER; }
[(] { fprintf(stdout,"OB:%s\n",yytext); return OB; }
[)] { fprintf(stdout,"CB:%s\n",yytext); return CB; }
[{] { fprintf(stdout,"COB:%s\n",yytext); return COB; }
[}] { fprintf(stdout,"CCB:%s\n",yytext); return CCB; }
[[] { fprintf(stdout,"SOB:%s\n",yytext); return SOB; }
[]] { fprintf(stdout,"SCB:%s\n",yytext); return SCB; }
[+] { fprintf(stdout,"ADD:%s\n",yytext); return ADD; }
[-] { fprintf(stdout,"SUB:%s\n",yytext); return SUB; }
[*] { fprintf(stdout,"MUL:%s\n",yytext); return MUL; }
[/] { fprintf(stdout,"DIV:%s\n",yytext); return DIV; }
[%] { fprintf(stdout,"PER:%s\n",yytext); return PER; }
[<] { fprintf(stdout,"LT:%s\n",yytext); return LT; }
[>] { fprintf(stdout,"GT:%s\n",yytext); return GT; }
[!] { fprintf(stdout,"NOT:%s\n",yytext); return NOT; }
[<][=] { fprintf(stdout,"LTEQ:%s\n",yytext); return LTEQ; }
[>][=] { fprintf(stdout,"GTEQ:%s\n",yytext); return GTEQ; }
[=] { fprintf(stdout,"EQ:%s\n",yytext); return EQ; }
[=][=] { fprintf(stdout,"EQEQ:%s\n",yytext); return EQEQ; }
[!][=] { fprintf(stdout,"NEQ:%s\n",yytext); return NEQ; }
[&][&] { fprintf(stdout,"AND:%s\n",yytext); return AND; }
[|][|] { fprintf(stdout,"OR:%s\n",yytext); return OR; }
[\n]     { fprintf(stdout,"EOL%s",yytext); return EOL; }
[ \t]  { /* ignore whitespace */ }
[,] { fprintf(stdout,"COMMA:%s\n",yytext) ; return COMMA; }
[;] { fprintf(stdout,"SEMICOLON:%s\n",yytext); return SEMICOLON; }
.      { fprintf(stdout,"Mystery character %s\n", yytext); }
%%
main(int argc, char **argv)
{
  int tok;
  while(tok = yylex()) {
    // printf("%d", tok);
    // if(tok == INTEGER_LITERAL) printf(" = %d\n", yylval);
    // else printf("\n");
  }
}
