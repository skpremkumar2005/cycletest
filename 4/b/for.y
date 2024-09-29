%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token TYPE RETURN ID NUM
%right '='
%left '+' '-'
%left '*' '/'
%right UMINUS
%left '!'

%%
S : FUN { printf("Input accepted\n"); exit(0); }
;

FUN : TYPE ID '(' PARAM ')' '{' BODY '}'
;

PARAM : PARAM ',' TYPE ID  // Multiple parameters
      | TYPE ID            // Single parameter
      |                     // Epsilon (no parameters)
;

BODY : BODY BODY             // Multiple statements
     | STATEMENT              // Single statement
;

STATEMENT : PARAM ';'        // Variable declaration
          | E ';'            // Expression statement
          | RETURN E ';'     // Return statement
;

E : ID '=' E                  // Assignment
  | E '+' E                    // Addition
  | E '-' E                    // Subtraction
  | E '*' E                    // Multiplication
  | E '/' E                    // Division
  | ID                         // Identifier
  | NUM                        // Numeric literal
;

%%
void yyerror(const char *s) {
    fprintf(stderr, "ERROR: %s\n", s);
}

int main() {
    printf("Enter the function definition:\n");
    yyparse();
    return 0;
}
