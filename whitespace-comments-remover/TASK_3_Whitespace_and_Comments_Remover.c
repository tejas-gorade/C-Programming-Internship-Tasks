#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Using int for character handling to properly detect EOF
void removeCommentsAndSpaces(FILE *src, FILE *dest) {
    int c, next;
    int inString = 0;
    int inChar = 0;

    while ((c = fgetc(src)) != EOF) {
        
        // 1. Handle String Literals "..."
        if (c == '"' && !inChar) {
            fputc(c, dest);
            inString = !inString;
            continue;
        }

        // 2. Handle Character Literals '...' 
        if (c == '\'' && !inString) {
            fputc(c, dest);
            inChar = !inChar;
            continue;
        }

        // If inside a string or a character literal, copy everything as-is
        if (inString || inChar) {
            fputc(c, dest);
            // Handle escaped characters like \" or \'
            if (c == '\\') {
                c = fgetc(src);
                if (c != EOF) fputc(c, dest);
            }
            continue;
        }

        // 3. Handle Comments (Only when NOT in string/char)
        if (c == '/') {
            next = fgetc(src);

            if (next == '/') { // Single-line comment
                while ((c = fgetc(src)) != EOF && c != '\n');
                if (c == '\n') fputc('\n', dest);
            } 
            else if (next == '*') { // Multi-line comment
                while ((c = fgetc(src)) != EOF) {
                    if (c == '*') {
                        next = fgetc(src);
                        if (next == '/') break;
                        else if (next != EOF) ungetc(next, src);
                    }
                }
            } 
            else { // Just a slash
                fputc(c, dest);
                if (next != EOF) ungetc(next, src);
            }
        } 
        // 4. Compress Multiple Spaces/Tabs
        else if (c == ' ' || c == '\t') {
            // Peek at next character
            next = fgetc(src);
            // Only add a space if the next character isn't a newline or more space
            if (next != '\n' && next != '\r' && next != EOF) {
                fputc(' ', dest);
                while ((next = fgetc(src)) == ' ' || next == '\t');
            }
            if (next != EOF) ungetc(next, src);
        } 
        // 5. Regular characters
        else {
            fputc(c, dest);
        }
    }
}

int main() {
    FILE *src, *dest;
    char inputFile[100], outputFile[100];

    printf("===== 🛠️ Lexical Pre-processor (Optimized) =====\n");
    
    printf("Enter source file name: ");
    if (scanf("%99s", inputFile) != 1) return 1;

    printf("Enter output file name: ");
    if (scanf("%99s", outputFile) != 1) return 1;

    src = fopen(inputFile, "r");
    if (!src) {
        perror("❌ Source file error");
        return 1;
    }

    dest = fopen(outputFile, "w");
    if (!dest) {
        perror("❌ Output file error");
        fclose(src);
        return 1;
    }

    removeCommentsAndSpaces(src, dest);

    fclose(src);
    fclose(dest);

    printf("\n✅ Code cleaned successfully!\n");
    return 0;
}
