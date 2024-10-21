%{
#include <stdio.h>
#include "y.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[ \t]       ; // Ignore whitespace
\n          { return 0; }
.           { return yytext[0]; } // Return any other character
%% 

int yywrap() {
    return 1;
}

