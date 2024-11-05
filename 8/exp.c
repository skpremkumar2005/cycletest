#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Structure to represent a register
typedef struct {
    char var[10];
    int alive;
} Register;

Register registers[10] = {0};  // Initialize all registers as unused

// Function to get an available register
int getRegister() {
    for (int i = 0; i < 10; i++) {
        if (registers[i].alive == 0) {
            registers[i].alive = 1;
            return i;
        }
    }
    return -1;
}

// Function to parse the three address code and extract components
void parseInstruction(char* input, char* result, char* op1, char* op2, char* operator) {
    char* token;
    
    // Get result (left side of =)
    token = strtok(input, "=");
    sscanf(token, "%s", result);
    
    // Get the rest of the expression
    token = strtok(NULL, "=");
    
    // Extract first operand
    while (*token == ' ') token++; // Skip leading spaces
    int i = 0;
    while (*token != ' ' && *token != '\0' && !strchr("+-*/", *token)) {
        op1[i++] = *token++;
    }
    op1[i] = '\0';
    
    // Extract operator
    while (*token == ' ') token++; // Skip spaces
    *operator = *token;
    token++;
    
    // Extract second operand
    while (*token == ' ') token++; // Skip spaces
    sscanf(token, "%s", op2);
}

int main() {
    char instruction[50];
    char result[10], op1[10], op2[10], operator;
    char instructions[100][50];  // Store instructions
    int instruction_count = 0;
    
    printf("Enter the Three Address Code (type 'exit' to end input):\n");
    
    // Read all instructions first
    while (1) {
        fgets(instruction, sizeof(instruction), stdin);
        instruction[strcspn(instruction, "\n")] = 0; // Remove newline
        
        if (strcmp(instruction, "exit") == 0) {
            break;
        }
        
        strcpy(instructions[instruction_count++], instruction);
    }
    
    // Print the assembly code header
    printf("\nThe Equivalent Assembly Code is:\n");
    
    // Process each instruction
    for (int i = 0; i < instruction_count; i++) {
        // Parse the instruction
        parseInstruction(instructions[i], result, op1, op2, &operator);
        
        // Get registers for operands
        int reg1 = getRegister();
        int reg2 = getRegister();
        
        // Generate assembly code with proper indentation
        printf("\tMOV R%d, %s\n", reg1, op1);
        printf("\tMOV R%d, %s\n", reg2, op2);
        
        switch (operator) {
            case '+':
                printf("\tADD R%d, R%d\n", reg1, reg2);
                break;
            case '-':
                printf("\tSUB R%d, R%d\n", reg1, reg2);
                break;
            case '*':
                printf("\tMUL R%d, R%d\n", reg1, reg2);
                break;
            case '/':
                printf("\tDIV R%d, R%d\n", reg1, reg2);
                break;
        }
        
        printf("\tMOV %s, R%d\n", result, reg1);
        
        if (i < instruction_count - 1) {
            printf("\n");  // Add blank line between instructions
        }
        
        // Free the registers
        registers[reg1].alive = 0;
        registers[reg2].alive = 0;
    }
    
    return 0;
}
