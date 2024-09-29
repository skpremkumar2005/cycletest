%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token ID SC INT CHAR FLOAT BL BLVAL CHVAL REAL AS NUM COMMA NL

%%
s: type1 | type2 | type3 | type4 ;

type1: INT varlist SC NL { printf("Valid INT Variable declaration\n"); return 0; }
type2: FLOAT varlist SC NL { printf("Valid FLOAT Variable declaration\n"); return 0; }
type3: CHAR varlist SC NL { printf("Valid CHAR Variable declaration\n"); return 0; }
type4: BL varlist SC NL { printf("Valid BOOLEAN Variable declaration\n"); return 0; }

varlist: ID
        | ID COMMA varlist
        | ID AS NUM
        | ID AS NUM COMMA varlist
        | /* epsilon */ 
        ;

%%
void yyerror(const char *s) {
    fprintf(stderr, "ERROR: %s\n", s);
}

int main() {
    printf("Enter variable declarations:\n");
    yyparse();
    return 0;
}
