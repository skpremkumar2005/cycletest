#include <stdio.h>
#include <string.h>

struct Operation {
    char lhs;
    char rhs[20];
} operations[10], optimized[10];

void main() {
    int i, j, n, z = 0, k;
    char *p, temp;
    
    // Input: Number of operations
    printf("Enter the Number of Values: ");
    scanf("%d", &n);
    
    // Input: Left-hand side and right-hand side for each operation
    for (i = 0; i < n; i++) {
        printf("Left: ");
        scanf(" %c", &operations[i].lhs);  // Reading a single character
        printf("Right: ");
        scanf("%s", operations[i].rhs);    // Reading a string
    }

    // Display intermediate code
    printf("\nIntermediate Code:\n");
    for (i = 0; i < n; i++) {
        printf("%c = %s\n", operations[i].lhs, operations[i].rhs);
    }

    // Dead Code Elimination
    for (i = 0; i < n - 1; i++) {
        temp = operations[i].lhs;
        for (j = 0; j < n; j++) {
            p = strchr(operations[j].rhs, temp);  // Check if lhs is used in rhs
            if (p) {
                optimized[z].lhs = operations[i].lhs;
                strcpy(optimized[z].rhs, operations[i].rhs);
                z++;
                break;
            }
        }
    }

    // Include the last operation in the optimized code
    optimized[z].lhs = operations[n - 1].lhs;
    strcpy(optimized[z].rhs, operations[n - 1].rhs);
    z++;

    // Display after Dead Code Elimination
    printf("\nAfter Dead Code Elimination:\n");
    for (k = 0; k < z; k++) {
        printf("%c = %s\n", optimized[k].lhs, optimized[k].rhs);
    }

    // Common Subexpression Elimination
    for (i = 0; i < z; i++) {
        for (j = i + 1; j < z; j++) {
            if (strcmp(optimized[i].rhs, optimized[j].rhs) == 0) {  // Check for common subexpressions
                optimized[j].lhs = optimized[i].lhs;  // Replace with the common lhs
            }
        }
    }

    // Display after Common Subexpression Elimination
    printf("\nAfter Common Subexpression Elimination:\n");
    for (k = 0; k < z; k++) {
        printf("%c = %s\n", optimized[k].lhs, optimized[k].rhs);
    }

    // Optimized Code (remove duplicates)
    printf("\nOptimized Code:\n");
    for (i = 0; i < z; i++) {
        if (optimized[i].lhs != '\0') {
            printf("%c = %s\n", optimized[i].lhs, optimized[i].rhs);
        }
    }
}
