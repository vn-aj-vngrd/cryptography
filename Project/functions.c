#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "functions.h"

/**********************************
 * Key Generators
 **********************************/

int getRandomShift()
{
    srand(time(NULL));
    return rand() % 26;
}

char *generateOTP(char text[])
{
    int i;
    char *otp = (char *)malloc(sizeof(char) * strlen(text));
    for (i = 0; i < strlen(text); i++)
    {
        otp[i] = getRandomShift() + 'A';
    }
    return otp;
}

/**********************************
 * Encryption Functions
 **********************************/

char *reverse(char text[])
{
    char *transformed_text = (char *)calloc(strlen(text) + 1, sizeof(char));
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            transformed_text[i] =
                islower(text[i]) ? 'z' - (text[i] - 'a') : 'Z' - (text[i] - 'A');
        }
        else
        {
            transformed_text[i] = text[i];
        }
    }

    return transformed_text;
}

char *shift(char text[], char key[])
{
    char *transformed_text = (char *)calloc(strlen(text) + 1, sizeof(char));
    int i, j;

    for (i = 0, j = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            int shift = getRandomShift();
            key[j++] = shift;

            transformed_text[i] = islower(text[i])
                                      ? 'a' + (text[i] - 'a' + shift) % 26
                                      : 'A' + (text[i] - 'A' + shift) % 26;
        }
        else
        {
            transformed_text[i] = text[i];
        }
    }

    return transformed_text;
}

char *vernam(char text[], char key[])
{
    char *transformed_text = (char *)calloc(strlen(text) + 1, sizeof(char));
    int i, j;

    char *otp = generateOTP(text);

    for (i = 0; i < strlen(text); i++)
    {
        int text_val = toupper(text[i]) - 'A';
        int key_val = toupper(otp[i]) - 'A';

        int cipher_val = text_val ^ key_val;

        transformed_text[i] =
            islower(text[i]) ? cipher_val + 'a' : cipher_val + 'A';
    }

    strcat(key, otp);

    return transformed_text;
}

/**********************************
 * Utility Functions
 **********************************/

int menu()
{
    int choice;

    printf("Project Cryptograph\n");
    printf("-------------------\n");
    printf("[1] Encrypt/Decrypt\n");
    printf("[2] Exit\n");
    printf("\nSelect: ");

    scanf("%d", &choice);
    fflush(stdin);

    return choice;
}

/*
 * This function gets the text from a file.
 *
 * @param text The text to be read from the file.
 *
 * @return 1 if the text is read successfully, 0 otherwise.
 */

int getTextFromFile(char text[])
{
    char filename[MAX_SIZE];

    printf("Enter filename to open: ");
    scanf("%[^\n]", filename);
    fflush(stdin);

    FILE *file = fopen(strcat(filename, ".txt"), "r");
    if (!file)
    {
        return 0;
    }

    fgets(text, MAX_SIZE, file);
    fclose(file);

    return 1;
}

/*
 * This function saves the text to a file.
 *
 * @param text The text to be saved to the file.
 */

void saveTextToFile(char text[])
{
    char filename[MAX_SIZE];

    printf("Enter filename to save: ");
    scanf("%[^\n]", filename);
    fflush(stdin);

    FILE *file = fopen(strcat(filename, ".txt"), "w");
    if (!file)
    {
        printf("Failed to save file.");
    }

    fprintf(file, "%s", text);
    fclose(file);

    printf("File saved successfully.");
}