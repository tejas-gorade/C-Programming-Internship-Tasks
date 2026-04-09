#include <stdio.h>
#include <stdlib.h>

// Function to compress a file using Run-Length Encoding
void compressFile(const char* sourceFile, const char* outputFile) {
    // Opening in binary mode for cross-platform stability (handling \r\n correctly)
    FILE *src = fopen(sourceFile, "rb");
    FILE *dest = fopen(outputFile, "wb");

    // Fix 1: Properly handle closing if one file fails and the other opens
    if (src == NULL || dest == NULL) {
        perror("❌ File error");
        if (src) fclose(src);
        if (dest) fclose(dest);
        return;
    }

    int current, prev;
    int count = 0;

    // Fix 2: Handle empty file case and use 'int' for EOF safety
    prev = fgetc(src);
    if (prev == EOF) {
        printf("⚠️ Warning: Source file is empty.\n");
        fclose(src);
        fclose(dest);
        return;
    }
    
    count = 1;

    // Process the file byte by byte
    while ((current = fgetc(src)) != EOF) {
        // Limit count to 99 to keep the output format (2 digits + char) predictable
        if (current == prev && count < 99) { 
            count++;
        } else {
            // Text-based RLE output for better readability during the internship showcase
            fprintf(dest, "%d%c", count, prev);
            prev = current;
            count = 1;
        }
    }

    // Write the last sequence
    fprintf(dest, "%d%c", count, prev);

    // Get final sizes using file pointers before closing
    fseek(src, 0, SEEK_END);
    long originalSize = ftell(src);
    
    fseek(dest, 0, SEEK_END);
    long compressedSize = ftell(dest);

    fclose(src);
    fclose(dest);

    // Display performance metrics
    printf("\n✅ Compression Complete!\n");
    printf("📂 Source: %ld bytes\n", originalSize);
    printf("💾 Target: %ld bytes\n", compressedSize);
    
    if (originalSize > 0) {
        float ratio = ((float)compressedSize / originalSize) * 100;
        printf("📊 Size Ratio: %.2f%% of original size\n", ratio);
    }
}

int main() {
    char source[100], target[100];

    printf("===== 🗜️ RLE Data Compressor =====\n");
    
    printf("Enter source filename: ");
    if (scanf("%99s", source) != 1) return 1;

    printf("Enter target filename: ");
    if (scanf("%99s", target) != 1) return 1;

    compressFile(source, target);

    return 0;
}
