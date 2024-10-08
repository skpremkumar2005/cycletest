%{
#include <stdio.h>
#include "y.tab.h"
%}

DIGIT [0-9]
REAL {DIGIT}+[.]{DIGIT}*
LETTER [A-Za-z]
ASSIGN =

%%
[\t ] ;  // Ignore spaces and tabs

int     { printf("%s\t==> DataType\n", yytext); return INT; }
float   { printf("%s\t==> DataType\n", yytext); return FLOAT; }
char    { printf("%s\t==> DataType\n", yytext); return CHAR; }
boolean  { printf("%s\t==> DataType\n", yytext); return BL; }

true|false { printf("%s\t==> BOOLEAN VAL\n", yytext); return BLVAL; }
'[^']'   { printf("%s\t==> CHAR VALUE\n", yytext); return CHVAL; }
{LETTER}({LETTER}|{DIGIT}|_)* { printf("%s\t==> ID\n", yytext); return ID; }
{REAL}   { printf("%s\t==> REAL NUMBER\n", yytext); return REAL; }
{DIGIT}+ { printf("%s\t==> INT NUMBER\n", yytext); return NUM; }
","      { printf("%s\t==> COMMA\n", yytext); return COMMA; }
";"      { printf("%s\t==> SC\n", yytext); return SC; }
{ASSIGN} { printf("%s\t==> ASSIGN\n", yytext); return AS; }
\n       { return NL; }
.        { /* Ignore other characters */ }
%%

int yywrap() {
    return 1;
}
