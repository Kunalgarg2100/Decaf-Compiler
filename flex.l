/* recognize tokens for the calculator and print them out */
%{
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
     OR = 296
    };
    int  yylval;
%}
digit [0-9]
letter [a-zA-Z]
alpha {letter}|[-]
alpha_num {alpha}|{digit}
hex_digit {digit}|[a-fA-F]
%%
"Program" { return PROGRAM; }
"class" { return CLASS; }
"callout" { return CALLOUT; }
"break" { return BREAK; }
"if" { return IF; }
"else" { return ELSE; }
"int" | "boolean" { return DATA_TYPE; }
"continue" { return CONTINUE; }
"return" { return RETURN; }
"for" { return FOR; }
"void" { return VOID; }
[(] { return OB; }
[)] { return CB; }
[{] { return COB; }
[}] { return CCB; }
[[] { return SOB; }
[]] { return SCB; }
[+] { return ADD; }
[-] { return SUB; }
[*] { return MUL; }
[/] { return DIV; }
[%] { return PER; }
[<] { return LT; }
[>] { return GT; }
[!] { return NOT; }
[<][=] { return LTEQ; }
[>][=] { return GTEQ; }
[=] { return EQ; }
[=][=] { return EQEQ; }
[!][=] { return NEQ; }
[&][&] { return AND; }
[|][|] { return OR; }
[\n]     { return EOL; }
[ \t]  { /* ignore whitespace */ }
{digit}+ { return INTEGER_LITERAL; }
"0x"{hex_digit}+ { return INTEGER_LITERAL; }
"true" | "false" { return BOOL_LITERAL; }
'(\\.|[^'\\\n])'  { return CHAR_LITERAL; }
\"(\\.|[^"])*\"  { return STRING; }
{alpha}+{alpha_num}* { return IDENTIFER; }
.      { printf("Mystery character %c\n", *yytext); }
%%
main(int argc, char **argv)
{
  int tok;
  while(tok = yylex()) {
    printf("%d", tok);
    if(tok == INTEGER_LITERAL) printf(" = %d\n", yylval);
    else printf("\n");
  }
}
