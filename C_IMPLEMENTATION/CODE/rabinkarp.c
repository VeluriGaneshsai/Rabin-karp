#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define d 256
#define MAX_LENGTH 1000

void search(char pat[], char txt[], int q) {
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; 
    int t = 0; 
    int h = 1;

    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (i = 0; i <= N - M; i++) {
        if (p == t) {
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j])
                    break;
            }
            if (j == M)
                printf("Pattern found at index %d \n", i);
        }
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
                t = (t + q);
        }
    }
}

int main() {
    char txt[MAX_LENGTH];
    char pat[MAX_LENGTH];
    char textFilePath[MAX_LENGTH];

    // Prompt the user to enter the file path for the text
    printf("Enter the file path for the text: ");
    scanf("%s", textFilePath);

    FILE *textFile = fopen(textFilePath, "r");
    if (textFile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Read both text and pattern strings from the file
    if (fscanf(textFile, " %[^\n] %[^\n]", txt, pat) != 2) {
        printf("Error reading text and pattern from file!\n");
        fclose(textFile);
        return 1;
    }
    
    fclose(textFile);

    // A prime number
    int q = 101;

    // Perform the search
    search(pat, txt, q);

    return 0;
}
