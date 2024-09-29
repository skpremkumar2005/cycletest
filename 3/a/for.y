%{
#include <stdio.h>
#include <stdlib.h>

int yylex();  // Forward declaration of yylex()
void yyerror(const char *s);  // Correct declaration of yyerror()
%}

%token ID NUM FOR LE GE EQ NE OR AND
%right '='
%left OR AND
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%right UMINUS
%left '!'
%%

S : ST { printf("Input accepted\n"); exit(0); }

ST : FOR '(' E ';' E2 ';' E ')' DEF ;

DEF : '{' BODY '}' 
    | E ';' 
    | ST
    | ;

BODY : BODY BODY 
     | E ';' 
     | ST 
     | ;

E : ID '=' E 
  | E '+' E 
  | E '-' E 
  | E '*' E 
  | E '/' E 
  | E '<' E 
  | E '>' E 
  | E LE E 
  | E GE E 
  | E EQ E 
  | E NE E 
  | E OR E 
  | E AND E 
  | E '+' '+' 
  | E '-' '-' 
  | ID 
  | NUM 
  ;

E2 : E '<' E 
   | E '>' E 
   | E LE E 
   | E GE E 
   | E EQ E 
   | E NE E 
   | E OR E 
   | E AND E 
   ;
%%

int main() {
    printf("Enter the expression:\n");
    yyparse();  // Call the parser
    return 0;
}

// Error handling function
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
