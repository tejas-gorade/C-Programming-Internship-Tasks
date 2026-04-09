#include <stdio.h>
#include <stdlib.h>

void removeCommentsAndSpaces(FILE *src, FILE *dest) {
    char c, next;

    while ((c = fgetc(src)) != EOF) {
        // 1. Handle potential comments
        if (c == '/') {
            next = fgetc(src);

            // Single-line comment: // ...
            if (next == '/') {
                while ((c = fgetc(src)) != EOF && c != '\n');
            } 
            // Multi-line comment: /* ... */
            else if (next == '*') {
                while ((c = fgetc(src)) != EOF) {
                    if (c == '*' && (next = fgetc(src)) == '/') {
                        break;
                    }
                }
            } 
            // Not a comment, just a single '/'
            else {
                fputc(c, dest);
                if (next != EOF) {
                    ungetc(next, src);
                }
            }
        } 
        // 2. Handle whitespaces (spaces, tabs, newlines)
        else if (c == ' ' || c == '\t' || c == '\n') {
            fputc(' ', dest); // Replace any sequence with a single space
            while ((next = fgetc(src)) == ' ' || next == '\t' || next == '\n');
            if (next != EOF) {
                ungetc(next, src);
            }
        } 
        // 3. Regular characters
        else {
            fputc(c, dest);
        }
    }
}

int main() {
    FILE *src, *dest;
    char inputFile[50], outputFile[50];

    printf("Enter source file name: ");
    scanf("%s", inputFile);
    printf("Enter output file name: ");
    scanf("%s", outputFile);

    src = fopen(inputFile, "r");
    dest = fopen(outputFile, "w");

    if (src == NULL || dest == NULL) {
        printf("Error: Cannot open file.\n");
        exit(0);
    }

    removeCommentsAndSpaces(src, dest);

    fclose(src);
    fclose(dest);

    printf("Comments and extra spaces removed. Output written to %s\n", outputFile);

    return 0;
}