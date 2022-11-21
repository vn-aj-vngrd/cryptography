#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALPHA 26
#define MAX_SIZE 255

int menu();
char *generateKey(char[]);
char *encrypt(char[], char[]);
char *decrypt(char[], char[]);
int getTextFromFile(char[], char[]);
void saveTextToFile(char[], char[]);

int main()
{
    do
    {
        char text[MAX_SIZE];

        int choice = menu();
        if (choice == 1)
        {
            int res = getTextFromFile(text, "plaintext");
            if (res)
            {
                printf("Plaintext: %s\n\n", text);

                char *key = generateKey(text);
                printf("Generated Key: %s\n\n", key);

                char *encrypted_text = encrypt(text, key);
                printf("Ciphertext: %s\n", encrypted_text);

                saveTextToFile(encrypted_text, "ciphertext");
            }
            else
            {
                printf("Error: Failed to read the file.");
            }
        }
        else if (choice == 2)
        {
            int res = getTextFromFile(text, "ciphertext");
            if (res)
            {
                printf("Ciphertext: %s\n\n", text);

                char *key = generateKey(text);
                printf("Generated Key: %s\n\n", key);

                char *decrypted_text = decrypt(text, key);
                printf("Plaintext: %s\n", decrypted_text);

                saveTextToFile(decrypted_text, "plaintext");
            }
            else
            {
                printf("Error: Failed to read the file.");
            }
        }
        else if (choice == 3)
        {
            printf("Thank you for using this program.");
            break;
        }
        else
        {
            printf("Invalid choice!");
        }

        printf("\n\n");

    } while (1);

    return 0;
}

int menu()
{
    int choice;

    printf("--------------------------\n");
    printf("Polyalphabetic Cryptograph\n");
    printf("--------------------------\n");
    printf("[1] Encrypt\n");
    printf("[2] Decrypt\n");
    printf("[3] Exit\n");
    printf("\nSelect: ");

    scanf("%d", &choice);
    fflush(stdin);

    return choice;
}

/*
 * Generates a key by the repition of the key_val
 * until the length of the key is equal to the length of the plain_text
 *
 * @param plain_text
 *
 * @return key
 *
 * Example:
 * text = "HELLO WORLD!"
 * key_val = "EARTH"
 * key = "EARTH EARTHE"
 */

char *generateKey(char text[])
{
    // Get key from user input
    char key_val[MAX_SIZE];
    printf("Input key: ");
    scanf("%[^\n]", key_val);
    fflush(stdin);

    // Create an allocated space for the new_key text to be returned.
    char *new_key = (char *)calloc((strlen(text) + 1), sizeof(char));

    int i, j;
    // Loop/Traverse through the text and key_val.
    for (i = 0, j = 0; i < strlen(text); i++)
    {
        // If the key_val is traversed completely, go back to the first index
        if (j == strlen(key_val))
            j = 0;

        // If the text is a space, add a space to the new_key.
        //  Else, copy the uppercased character of key_val
        new_key[i] = text[i] == ' ' ? ' ' : toupper(key_val[j++]);
    }

    return new_key;
}

/*
 * Encrypts the plain_text using the key.
 *
 * @param plain_text
 * @param key
 * @return encrypted_text
 *
 * Example:
 *  plain_text = "HELLO WORLD!"
 *  key_val = "EARTH"
 *  generated_key = "EARTH EARTHE"
 *  encrypted_text = "LECEV AOIEK!"
 */

char *encrypt(char plain_text[], char key[])
{
    // Create an allocated space for the encrypted text to be returned.
    char *encrypted_text = (char *)calloc(strlen(plain_text) + 1, sizeof(char));
    int i;

    // Loop/Traverse through plain_text
    for (i = 0; i < strlen(plain_text); i++)
    {
        // Formula: (plain_text[i] + key[i]) % 26
        if (isalpha(plain_text[i]))
        {
            // Encrypt letter using the formula
            int cipher_val = (toupper(plain_text[i]) + key[i]) % MAX_ALPHA;

            // Check if the letter is lowercase then return a lowercase letter else return an uppercase letter
            encrypted_text[i] = islower(plain_text[i]) ? (cipher_val + 'a')
                                                       : (cipher_val + 'A');
        }
        else
        {
            // If the current character is not a letter, just copy it.
            encrypted_text[i] = plain_text[i];
        }
    }

    return encrypted_text;
}

/*
 * Decrypts the encrypted_text using the key.
 *
 * @param cipher_text
 * @param key
 * @return decrypted_text
 *
 * Example:
 *  encrypted_text = "LECEV AOIEK!"
 *  key_val = "EARTH"
 *  generated_key = "EARTH EARTHE"
 *  decrypted_text = "HELLO WORLD!"
 */

char *decrypt(char cipher_text[], char key[])
{
    // Create an allocated space for the decrypted text to be returned.
    char *decrypted_text = (char *)calloc(strlen(cipher_text) + 1, sizeof(char));
    int i;

    // Loop/Traverse through cipher_text
    for (i = 0; i < strlen(cipher_text); i++)
    {
        // Formula: (cipher_text[i] - key[i] + 26) % 26
        if (isalpha(cipher_text[i]))
        {
            // Decrypt letters using the formula
            int plain_val = (toupper(cipher_text[i]) - key[i] + MAX_ALPHA) % MAX_ALPHA;

            // Check if the letter is lowercase then return a lowercase letter else return an uppercase letter
            decrypted_text[i] = islower(cipher_text[i]) ? (plain_val + 'a')
                                                        : (plain_val + 'A');
        }
        else
        {
            // If the current character is not a letter, just copy it.
            decrypted_text[i] = cipher_text[i];
        }
    }

    return decrypted_text;
}

/*
 * This function gets the text from a file.
 *
 * @param text The text to be read from the file.
 *
 * @return 1 if the text is read successfully, 0 otherwise.
 */

int getTextFromFile(char text[], char type[])
{
    char filename[MAX_SIZE];

    printf("Enter filename to open %s: ", type);
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

void saveTextToFile(char text[], char type[])
{
    char filename[MAX_SIZE];

    printf("Enter filename to save %s: ", type);
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