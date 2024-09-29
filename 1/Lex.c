#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

void main() {
    FILE *fi, *fo, *fop, *fk;
    int flag = 0, i = 1;
    char c, a[15], ch[15], file[20];

    printf("\nEnter the File Name: ");
    scanf("%s", file);

    fi = fopen(file, "r");
    if (fi == NULL) {
        fprintf(stderr, "Error opening input file: %s\n", strerror(errno));
        return;
    }

    fo = fopen("inter.c", "w");
    if (fo == NULL) {
        perror("Error opening intermediate file");
        fclose(fi);
        return;
    }

    fop = fopen("oper.c", "r");
    if (fop == NULL) {
        perror("Error opening operators file");
        fclose(fi);
        fclose(fo);
        return;
    }

    fk = fopen("key.c", "r");
    if (fk == NULL) {
        perror("Error opening keywords file");
        fclose(fi);
        fclose(fo);
        fclose(fop);
        return;
    }

    // Read the input file and process it
    while ((c = getc(fi)) != EOF) {
        if (isalpha(c) || isdigit(c) || c == '[' || c == ']' || c == '.') {
            fputc(c, fo);
        } else {
            if (c == '\n') {
                fprintf(fo, "\t$\t");  // Line ending token
            } else {
                fprintf(fo, "\t%c\t", c);  // Other symbols
            }
        }
    }
    fclose(fi);
    fclose(fo);

    fi = fopen("inter.c", "r");
    if (fi == NULL) {
        perror("Error reopening intermediate file");
        fclose(fop);
        fclose(fk);
        return;
    }

    printf("\nLexical Analysis\n");
    fscanf(fi, "%s", a);
    printf("\nLine: %d\n", i++);

    while (!feof(fi)) {
        if (strcmp(a, "$") == 0) {
            printf("\nLine: %d \n", i++);
            fscanf(fi, "%s", a);
        }

        // Check against operators
        fscanf(fop, "%s", ch);
        while (!feof(fop)) {
            if (strcmp(ch, a) == 0) {
                fscanf(fop, "%s", ch);
                printf("\t\t%s\t:\t%s\n", a, ch);
                flag = 1;
            }
            fscanf(fop, "%s", ch);
        }
        rewind(fop);

        // Check against keywords
        fscanf(fk, "%s", ch);
        while (!feof(fk)) {
            if (strcmp(ch, a) == 0) {
                printf("\t\t%s\t:\tKeyword\n", a);
                flag = 1;
            }
            fscanf(fk, "%s", ch);
        }
        rewind(fk);

        if (flag == 0) {
            if (isdigit(a[0])) {
                printf("\t\t%s\t:\tConstant\n", a);
            } else {
                printf("\t\t%s\t:\tIdentifier\n", a);
            }
        }
        flag = 0;
        fscanf(fi, "%s", a);
    }

    fclose(fi);
    fclose(fop);
    fclose(fk);
}
