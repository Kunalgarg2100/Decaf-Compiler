/* recognize tokens for the Program and print them out */
%{
    #include "parser.tab.h"
    FILE *outfile = fopen("flex_output.txt", "w+");
%}
digit [0-9]
letter [a-zA-Z]
alpha {letter}|[_]
alpha_num {alpha}|{digit}
hex_digit {digit}|[a-fA-F]
char (\\.|[^'\\\n])
string (\\.|[^"])*
%%
"Program" { fprintf(outfile,"PROGRAM\n"); return PROGRAM; }
"class" { fprintf(outfile,"CLASS\n"); return CLASS; }
"callout" { fprintf(outfile,"CALLOUT\n"); return CALLOUT; }
"break" { fprintf(outfile,"BREAK\n"); return BREAK; }
"if" { fprintf(outfile,"IF\n"); return IF; }
"else" { fprintf(outfile,"ELSE\n"); return ELSE; }
"for" { fprintf(outfile,"FOR\n"); return FOR; }
"return" { fprintf(outfile,"RETURN\n"); return RETURN; }
"void" { fprintf(outfile,"VOID\n");  yylval.str = strdup(yytext); return VOID; }
"continue" { fprintf(outfile,"CONTINUE\n"); return CONTINUE; }
"int"|"boolean" { fprintf(outfile,"DATA_TYPE:%s\n",yytext); yylval.str = strdup(yytext); return DATA_TYPE; }
"true"|"false" { fprintf(outfile,"BOOL_LITERAL:%s\n",yytext); yylval.str = strdup(yytext); return BOOL_LITERAL; }
{digit}+|"0x"{hex_digit}+ { fprintf(outfile,"INTEGER_LITERAL:%s\n",yytext); yylval.val = atoi(yytext); return INTEGER_LITERAL; }
'{char}'  { fprintf(outfile,"CHAR_LITERAL:%s\n",yytext); yylval.ch = strdup(yytext)[1]; return CHAR_LITERAL; }
\"{string}\"  { fprintf(outfile,"STRING:%s\n",yytext); yylval.str = strdup(yytext); return STRING; }
{alpha}+{alpha_num}* { fprintf(outfile,"IDENTIFER:%s\n",yytext);yylval.str = strdup(yytext); return ID; }
[(] { fprintf(outfile,"OB:%s\n",yytext); return OB; }
[)] { fprintf(outfile,"CB:%s\n",yytext); return CB; }
[{] { fprintf(outfile,"COB:%s\n",yytext); return COB; }
[}] { fprintf(outfile,"CCB:%s\n",yytext); return CCB; }
[[] { fprintf(outfile,"SOB:%s\n",yytext); return SOB; }
[]] { fprintf(outfile,"SCB:%s\n",yytext); return SCB; }
[+] { fprintf(outfile,"ADD:%s\n",yytext); yylval.str = strdup(yytext); return ADD; }
[-] { fprintf(outfile,"SUB:%s\n",yytext); yylval.str = strdup(yytext); return SUB; }
[*] { fprintf(outfile,"MUL:%s\n",yytext); yylval.str = strdup(yytext); return MUL; }
[/] { fprintf(outfile,"DIV:%s\n",yytext); yylval.str = strdup(yytext); return DIV; }
[%] { fprintf(outfile,"MOD:%s\n",yytext); yylval.str = strdup(yytext); return MOD; }
[<] { fprintf(outfile,"LT:%s\n",yytext); yylval.str = strdup(yytext); return LT; }
[>] { fprintf(outfile,"GT:%s\n",yytext); yylval.str = strdup(yytext); return GT; }
[!] { fprintf(outfile,"NOT:%s\n",yytext); yylval.str = strdup(yytext); return NOT; }
[=] { fprintf(outfile,"EQ:%s\n",yytext); yylval.str = strdup(yytext); return EQ; }
[<][=] { fprintf(outfile,"LTEQ:%s\n",yytext); yylval.str = strdup(yytext); return LTEQ; }
[>][=] { fprintf(outfile,"GTEQ:%s\n",yytext); yylval.str = strdup(yytext); return GTEQ; }
[=][=] { fprintf(outfile,"EQEQ:%s\n",yytext); yylval.str = strdup(yytext); return EQEQ; }
[!][=] { fprintf(outfile,"NEQ:%s\n",yytext); yylval.str = strdup(yytext); return NEQ; }
[+][=] { fprintf(outfile,"PLUSEQ:%s\n",yytext); yylval.str = strdup(yytext); return PLUSEQ; }
[-][=] { fprintf(outfile,"MINUSEQ:%s\n",yytext); yylval.str = strdup(yytext); return MINUSEQ; }
[&][&] { fprintf(outfile,"AND:%s\n",yytext); yylval.str = strdup(yytext); return AND; }
[|][|] { fprintf(outfile,"OR:%s\n",yytext); yylval.str = strdup(yytext); return OR; }
[ \t\n]+  { /* ignore whitespace */ }
[,] { fprintf(outfile,"COMMA:%s\n",yytext) ; return COMMA; }
[;] { fprintf(outfile,"SEMICOLON:%s\n",yytext); return SEMICOLON; }
.   { fprintf(outfile,"Mystery character %s\n", yytext); }
%%