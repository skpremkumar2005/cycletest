%{
/* Definition section */
#include<stdio.h>
%}

/* Rule Section */
%%
[6-9][0-9]{9} { printf("\nMobile Number Valid\n"); } // A valid mobile number starts with a digit 1-9 and has exactly 9 more digits.
.+ { printf("\nMobile Number Invalid\n"); } // For any other input, print invalid.
%%

// Driver code
int main() {
    printf("\nEnter Mobile Number: ");
    yylex();  // Start the lexical analysis process
    printf("\n");
    return 0;
}
