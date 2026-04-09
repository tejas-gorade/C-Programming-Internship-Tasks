#include <stdio.h>
#include <conio.h> // for getch() on Windows

int main() {
    char prev, c;
    int count = 0;

    printf("Type text (press ENTER to finish):\n");

    // Get the first character
    prev = getch(); 
    if (prev == 13) { // If user presses ENTER immediately
        return 0;
    }
    
    printf("%c", prev); // Show what user typed
    count = 1;

    // Loop until ENTER (ASCII 13) is pressed
    while ((c = getch()) != 13) { 
        printf("%c", c); // Echo the character to the screen

        if (c == prev) {
            count++;
        } else {
            // Print the compression result for the previous character sequence
            printf(" -> Compressed: %d%c\n", count, prev);
            
            // Reset for the new character
            prev = c;
            count = 1;
        }
    }

    // Print the final character set after ENTER is pressed
    printf(" -> Compressed: %d%c\n", count, prev);
    printf("\n✅ Input compressed successfully!\n");

    return 0;
}