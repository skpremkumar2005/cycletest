%{
#include<stdio.h>

int lc = 0, sc = 0, tc = 0, ch = 0; /* Global counters */
int yywrap() {
    return 1;  // Tells Lex that the end of input has been reached
}
%}

/* Rule Section */
%%
\n     lc++;          // Line counter
[ ]+   sc++;          // Space counter
\t     tc++;          // Tab counter
.      ch++;          // Character counter
%%

int main() {
    // Start lexical analysis
    yylex();

    // Output the results
    printf("\nNo. of lines = %d", lc);
    printf("\nNo. of spaces = %d", sc);
    printf("\nNo. of tabs = %d", tc);
    printf("\nNo. of other characters = %d\n", ch);

    return 0;
}
