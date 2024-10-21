%{
#include "y.tab.h"
#include <stdio.h>
%}

%%
[0-9]+      { yylval.symbol = (char)(atoi(yytext)); return NUMBER; }
[a-z]       { yylval.symbol = (char)(yytext[0]); return LETTER; }
[=+\-*/()]  { return yytext[0]; }
[ \t]       ; // Ignore whitespace
\n          { return 0; }
.           { return yytext[0]; }

%%

