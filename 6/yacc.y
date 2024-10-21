%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_EXPRS 20

struct expr {
    char operand1;
    char operand2;
    char operator;
    char result;
};

struct expr arr[MAX_EXPRS];
int index1 = 0;
char temp = 'A' - 1;

char addtotable(char a, char b, char o);
void threeAdd();
void yyerror(const char *s);
int yylex();

%}

%union {
    char symbol;
}

%left '+' '-'
%left '*' '/'
%token <symbol> LETTER NUMBER
%type <symbol> exp

%%

// Grammar rules
statement: LETTER '=' exp ';' {
    addtotable((char)$1, (char)$3, '=');
}
;

exp: exp '+' exp {
    $$ = addtotable((char)$1, (char)$3, '+');
}
| exp '-' exp {
    $$ = addtotable((char)$1, (char)$3, '-');
}
| exp '*' exp {
    $$ = addtotable((char)$1, (char)$3, '*');
}
| exp '/' exp {
    $$ = addtotable((char)$1, (char)$3, '/');
}
| '(' exp ')' {
    $$ = (char)$2;
}
| NUMBER {
    $$ = (char)$1;
}
| LETTER {
    $$ = (char)$1;
}
;

%%

// Function definitions
char addtotable(char a, char b, char o) {
    temp++;
    arr[index1].operand1 = a;
    arr[index1].operand2 = b;
    arr[index1].operator = o;
    arr[index1].result = temp;
    index1++;
    return temp;
}

void threeAdd() {
    for (int i = 0; i < index1; i++) {
        printf("%c := %c %c %c\n", arr[i].result, arr[i].operand1, arr[i].operator, arr[i].operand2);
    }
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int yywrap() {
    return 1;
}

int main() {
    printf("Enter the expression: ");
    yyparse();
    printf("\nThree Address Code:\n");
    threeAdd();
    return 0;
}

