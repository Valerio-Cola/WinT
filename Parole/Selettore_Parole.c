#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 100

int main(int argc, char *argv[]) {
    FILE *inputFile = fopen("660000_parole_italiane.txt", "r");
    char outputFileName[20];
    snprintf(outputFileName, sizeof(outputFileName), "parole%d.txt", atoi(argv[1]));
    FILE *outputFile = fopen(outputFileName, "w");
    char word[MAX_WORD_LENGTH];

    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <word_length>\n", argv[0]);
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    int wordLength = atoi(argv[1]);

    while (fgets(word, sizeof(word), inputFile) != NULL) {
        // Remove newline character if present
        word[strcspn(word, "\n")] = '\0';
        if (strlen(word) == wordLength) {
            fprintf(outputFile, "%s\n", word);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}