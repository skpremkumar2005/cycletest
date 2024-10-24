#include <stdio.h>
#include <string.h>
#include <ctype.h>
// #include <conio.h>

typedef struct {
    char var[10];
    int alive;
} regist;

regist preg[10];

void substring(char exp[], int st, int end) {
    int i, j = 0;
    char dup[10] = "";
    for (i = st; i < end; i++) {
        dup[j++] = exp[i];
    }
    dup[j] = '\0';  // Proper string termination
    strcpy(exp, dup);
}

int getregister(char var[]) {
    int i;
    for (i = 0; i < 10; i++) {
        if (preg[i].alive == 0) {  // Find first available register
            strcpy(preg[i].var, var);
            return i;
        }
    }
    return -1;  // In case no register is available
}

void getvar(char exp[], char v[]) {
    int i, j = 0;
    char var[10] = "";
    
    for (i = 0; exp[i] != '\0'; i++) {
        if (isalpha(exp[i])) {  // Get the first variable
            var[j++] = exp[i];
        } else {
            break;
        }
    }
    var[j] = '\0';  // Proper string termination
    strcpy(v, var);
}

void main() {
    char basic[10][10], var[10][10], fstr[10], op;
    int i, j, k, reg, vc = 0, flag = 0;

    clrscr();

    printf("\nEnter the Three Address Code (type 'exit' to stop):\n");
    
    // Input three address code
    for (i = 0; ; i++) {
        gets(basic[i]);
        if (strcmp(basic[i], "exit") == 0)  // Stop when user enters "exit"
            break;
    }

    printf("\nThe Equivalent Assembly Code is:\n");

    // Process each three-address code line
    for (j = 0; j < i; j++) {
        getvar(basic[j], var[vc++]);
        strcpy(fstr, var[vc - 1]);

        substring(basic[j], strlen(var[vc - 1]) + 1, strlen(basic[j]));

        getvar(basic[j], var[vc++]);
        reg = getregister(var[vc - 1]);

        if (preg[reg].alive == 0) {
            printf("\nMov R%d, %s", reg, var[vc - 1]);
            preg[reg].alive = 1;
        }

        op = basic[j][strlen(var[vc - 1])];

        substring(basic[j], strlen(var[vc - 1]) + 1, strlen(basic[j]));

        getvar(basic[j], var[vc++]);

        // Switch case to handle different operations
        switch (op) {
            case '+': printf("\nAdd "); break;
            case '-': printf("\nSub "); break;
            case '*': printf("\nMul "); break;
            case '/': printf("\nDiv "); break;
        }

        flag = 1;
        for (k = 0; k <= reg; k++) {
            if (strcmp(preg[k].var, var[vc - 1]) == 0) {
                printf("R%d, R%d", k, reg);
                preg[k].alive = 0;
                flag = 0;
                break;
            }
        }

        if (flag) {
            printf(" %s, R%d", var[vc - 1], reg);
            printf("\nMov %s, R%d", fstr, reg);
        }

        strcpy(preg[reg].var, var[vc - 3]);
    }

    getch();
}
