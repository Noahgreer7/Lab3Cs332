#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* lets main() call them even though they are defined later in the file. */

void readStrings(char *words[], int count);
void sortStrings(char *words[], int count);
void displayStrings(char *words[], int count);
void freeStrings(char *words[], int count);

int main() {
    int count;

    /* Ask the user how many strings they want to enter. */

    printf("Enter the number of strings: ");
    scanf("%d", &count);

    /* Make an array big enough to hold "count" strings.
     * Each slot in this array will hold the address of one string. */

    char **words = malloc(count * sizeof(char *));

    /* Fill the array by reading in each string from the user. */
    
    readStrings(words, count);

    printf("\nBefore sorting:\n");
    displayStrings(words, count);

    /* Sort the strings alphabetically. */

    sortStrings(words, count);

    printf("\nAfter sorting:\n");
    displayStrings(words, count);

    /* Give back all the memory we borrowed with malloc. */

    freeStrings(words, count);

    return 0;
}

/* Asks the user to type in "count" strings, one at a time.
 * For each string:
 *   - It is first typed into a temporary array called "tempBuffer".
 *   - measure how long it is using strlen.
 *   - malloc just enough space for it.
 *   - copy it into that new space using strcpy.
 *   - save the address of that space into the "words" array. */

void readStrings(char *words[], int count) {
    char tempBuffer[100];

    for (int i = 0; i < count; i++) {
        printf("Enter string %d: ", i + 1);
        scanf("%s", tempBuffer);

        int length = strlen(tempBuffer);

        words[i] = malloc(length + 1);

        strcpy(words[i], tempBuffer);
    }
}

/* Sorts the array of strings into alphabetical order using insertion sort.
 *   - look at each string one at a time.
 *   - compare it to the strings before it.
 *   - keep swapping it backwards until it is in the correct spot. */

 void sortStrings(char *words[], int count) {
    for (int i = 1; i < count; i++) {
        int j = i;

        /* Keep moving the string at position j backwards
         * as long as it belongs before the string in front of it. */

        while (j > 0 && strcmp(words[j], words[j - 1]) < 0) {

            /* Swap words[j] and words[j - 1] */

            char *temp = words[j];
            words[j] = words[j - 1];
            words[j - 1] = temp;

            j = j - 1;
        }
    }
}

/* Prints all the strings in the array, separated by commas,
 * inside square brackets. */

 void displayStrings(char *words[], int count) {
    printf("[");
    for (int i = 0; i < count; i++) {
        printf("%s", words[i]);

        /* Print a comma after every word except the last one */

        if (i < count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

/* Frees all the memory allocated with malloc. Free each individual string, then free the
 * array that was holding their addresses. */
void freeStrings(char *words[], int count) {
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}