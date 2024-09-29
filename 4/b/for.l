%{
#include <stdio.h>
#include "y.tab.h"
%}

alpha [A-Za-z]
digit [0-9]

%%
[\t \n] ;                     // Ignore whitespace
int|float|void|char   return TYPE;   // Data types
return              return RETURN;     // Return keyword
{digit}+           return NUM;        // Numeric literals
{alpha}({alpha}|{digit})* return ID;  // Identifiers
.                  return yytext[0];  // Any other character
%%

int yywrap() {
    return 1;
}
