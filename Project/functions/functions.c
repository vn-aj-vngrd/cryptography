#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "functions.h"

/*****************************************
 * Main Functions
 ****************************************/

char *encrypt(char text[])
{
    srand(time(NULL));
    int size = strlen(text);

    char *cipher_text = (char *)calloc(size + 1, sizeof(char));
    strcpy(cipher_text, text);

    char *key = (char *)calloc((size * 3) + (size / 2) + 1, sizeof(char));

    char *shift_key = generateKey(size);
    strcpy(key, shift_key);

    char *vigenere_key = generateKey(size);
    strncpy(key + size, vigenere_key, size);

    char *otp = generateKey(size);
    strncpy(key + size * 2, otp, size);

    int i;
    for (i = 0; i < MAX_ROUNDS; i++)
    {
        // Atbash
        atbash(cipher_text);

        // Shifting
        shift(cipher_text, shift_key);

        // Vigenere
        vigenere(cipher_text, vigenere_key, 1);

        // Vernam
        vernam(cipher_text, otp);
    }

    printf("\nKey: %s\n", key);
    saveTextToFile(key, "key");

    return cipher_text;
}

char *decrypt(char text[], char key[])
{
    int size = strlen(text);

    char *plain_text = (char *)calloc(size + 1, sizeof(char));
    strcpy(plain_text, text);

    char *otp = (char *)calloc(size + 1, sizeof(char));
    strncpy(otp, key + size * 2, size);

    char *vigenere_key = (char *)calloc(size + 1, sizeof(char));
    strncpy(vigenere_key, key + size, size);

    char *shift_key = (char *)calloc(size + 1, sizeof(char));
    strncpy(shift_key, key, size);
    char *new_shift_key = decryptShiftKey(shift_key);

    int i;
    for (i = 0; i < MAX_ROUNDS; i++)
    {
        // Vernam
        vernam(plain_text, otp);

        // Vigenere
        vigenere(plain_text, vigenere_key, 2);

        // Shifting
        shift(plain_text, new_shift_key);

        // Atbash
        atbash(plain_text);
    }

    return plain_text;
}

/*****************************************
 * Encryption/Decryption Utility Functions
 ****************************************/

void atbash(char text[])
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            text[i] =
                islower(text[i]) ? 'z' - (text[i] - 'a') : 'Z' - (text[i] - 'A');
        }
    }
}

void shift(char text[], char shift_key[])
{
    int i, j;

    for (i = 0, j = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            text[i] = islower(text[i])
                          ? 'a' + (text[i] - 'a' + shift_key[i]) % 26
                          : 'A' + (text[i] - 'A' + shift_key[i]) % 26;
        }
    }
}

void vigenere(char text[], char key[], int type)
{
    int vigenere_val;

    int i;
    for (i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            if (type == 1)
            {
                vigenere_val = (toupper(text[i]) + key[i]) % 26;
            }
            else
            {
                vigenere_val = (toupper(text[i]) - key[i] + 26) % 26;
            }

            text[i] = islower(text[i]) ? (vigenere_val + 'a') : (vigenere_val + 'A');
        }
    }
}

void vernam(char text[], char otp[])
{
    int i, j;

    for (i = 0; i < strlen(text); i++)
    {
        int text_val = toupper(text[i]) - 'A';
        int key_val = toupper(otp[i]) - 'A';

        int cipher_val = text_val ^ key_val;

        text[i] = islower(text[i]) ? cipher_val + 'a' : cipher_val + 'A';
    }
}

/*****************************************
 * Key Generators
 ****************************************/

char *generateKey(int size)
{
    char *shift_key = (char *)calloc(size + 1, sizeof(char));
    int i;

    for (i = 0; i < size; i++)
    {
        shift_key[i] = rand() % 26 + 'A';
    }

    return shift_key;
}

char *decryptShiftKey(char key[])
{
    char *shift_key = (char *)calloc(strlen(key) + 1, sizeof(char));
    int i;

    for (i = 0; i < strlen(key); i++)
    {
        shift_key[i] = 26 - (key[i] % 26);
    }

    return shift_key;
}

/*****************************************
 * Common Utility Functions
 ****************************************/

int menu()
{
    int choice;

    printf("-----------------\n");
    printf("Van's Cryptograph\n");
    printf("-----------------\n");
    printf("[1] Encrypt\n");
    printf("[2] Decrypt\n");
    printf("[3] Exit\n");
    printf("\nSelect an option\n> ");

    scanf("%d", &choice);
    fflush(stdin);

    return choice;
}

int getTextFromFile(char text[], char type[])
{
    char filename[MAX_SIZE];

    printf("\nEnter filename to open %s\n> ", type);
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

void saveTextToFile(char text[], char type[])
{
    char filename[MAX_SIZE];

    printf("Enter filename to save %s\n> ", type);
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