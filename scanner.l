/* recognize tokens for the Program and print them out */
%{
    #include "parser.tab.h"
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
"int"|"boolean" { fprintf(stdout,"DATA_TYPE:%s\n",yytext); yylval.str = strdup(yytext); return DATA_TYPE; }
"true"|"false" { fprintf(stdout,"BOOL_LITERAL:%s\n",yytext); yylval.str = strdup(yytext); return BOOL_LITERAL; }
{digit}+|"0x"{hex_digit}+ { fprintf(stdout,"INTEGER_LITERAL:%s\n",yytext); yylval.val = atoi(yytext); return INTEGER_LITERAL; }
'{char}'  { fprintf(stdout,"CHAR_LITERAL:%s\n",yytext); yylval.str = strdup(yytext); return CHAR_LITERAL; }
\"{string}\"  { fprintf(stdout,"STRING:%s\n",yytext); yylval.str = strdup(yytext); return STRING; }
{alpha}+{alpha_num}* { fprintf(stdout,"IDENTIFER:%s\n",yytext);yylval.str = strdup(yytext); return ID; }
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
[%] { fprintf(stdout,"MOD:%s\n",yytext); return MOD; }
[<] { fprintf(stdout,"LT:%s\n",yytext); return LT; }
[>] { fprintf(stdout,"GT:%s\n",yytext); return GT; }
[!] { fprintf(stdout,"NOT:%s\n",yytext); return NOT; }
[=] { fprintf(stdout,"EQ:%s\n",yytext); return EQ; }
[<][=] { fprintf(stdout,"LTEQ:%s\n",yytext); return LTEQ; }
[>][=] { fprintf(stdout,"GTEQ:%s\n",yytext); return GTEQ; }
[=][=] { fprintf(stdout,"EQEQ:%s\n",yytext); return EQEQ; }
[!][=] { fprintf(stdout,"NEQ:%s\n",yytext); return NEQ; }
[+][=] { fprintf(stdout,"PLUSEQ:%s\n",yytext); return PLUSEQ; }
[-][=] { fprintf(stdout,"MINUSEQ:%s\n",yytext); return MINUSEQ; }
[&][&] { fprintf(stdout,"AND:%s\n",yytext); return AND; }
[|][|] { fprintf(stdout,"OR:%s\n",yytext); return OR; }
[ \t]+  { /* ignore whitespace */ }
[,] { fprintf(stdout,"COMMA:%s\n",yytext) ; return COMMA; }
[;] { fprintf(stdout,"SEMICOLON:%s\n",yytext); return SEMICOLON; }
.   { fprintf(stdout,"Mystery character %s\n", yytext); }
%%