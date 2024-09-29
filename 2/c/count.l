%{
    int flag = 0;  /* Global flag to check if input matches email pattern */
%}

%%

[a-z0-9_]+@[a-z]+\.com|[a-z0-9_]+@[a-z]+\.in { 
    flag = 1;  /* Set flag if the input matches the pattern */
}

%%

int main() {
    yylex();  // Start lexical analysis

    if (flag == 1)
        printf("Accepted\n");  // If the pattern matches, print 'Accepted'
    else
        printf("Not Accepted\n");  // If no match, print 'Not Accepted'

    return 0;
}
