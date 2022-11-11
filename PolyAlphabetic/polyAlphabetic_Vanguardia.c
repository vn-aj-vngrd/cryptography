#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALPHA 26
#define MAX_NUM 10
#define MAX_SIZE 255

void menu();
char *generateKey(char[], char[]);
char *encrypt(char[], char[]);
char *decrypt(char[], char[]);

int main()
{
    char text[MAX_SIZE];
    char key_val[MAX_SIZE];
    int choice;

    do
    {
        menu();

        scanf("%d", &choice);
        fflush(stdin);

        if (choice == 1)
        {
            printf("Input text: ");
            scanf("%[^\n]", &text);
            fflush(stdin);

            printf("Input key: ");
            scanf("%[^\n]", &key_val);
            fflush(stdin);

            char *new_key = generateKey(text, key_val);
            printf("Generated Key: %s\n", new_key);

            char *encrypted_text = encrypt(text, new_key);
            printf("Encrypted Text: %s", encrypted_text);
        }
        else if (choice == 2)
        {
            printf("Input text: ");
            scanf("%[^\n]", &text);
            fflush(stdin);

            printf("Input key: ");
            scanf("%[^\n]", &key_val);
            fflush(stdin);

            char *new_key = generateKey(text, key_val);
            printf("Generated Key: %s\n", new_key);

            char *decrypted_text = decrypt(text, new_key);
            printf("Decrypted Text: %s", decrypted_text);
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

void menu()
{
    printf("[1] Encrypt\n");
    printf("[2] Decrypt\n");
    printf("[3] Exit\n");
    printf("\nSelect: ");
}

/*
 * Generates a key by the repition of the key_val
 * until the length of the key is equal to the length of the plain_text
 *
 * @param plain_text
 * @param key_val
 *
 * @return key
 *
 * Example:
 * text = "HELLOWORLD"
 * key_val = "EARTH"
 * key = "EARTHEARTH"
 */

char *generateKey(char plain_text[], char key_val[])
{
    // Create an allocated space for the new_key text to be returned.
    char *new_key = (char *)calloc((strlen(plain_text) + 1), sizeof(char));

    int i, j;
    // Loop/Traverse through the plain_text and key_val.
    for (i = 0, j = 0; i < strlen(plain_text); i++)
    {
        // If the key_val is traversed completely, go back to the first index
        if (j == strlen(key_val))
            j = 0;

        // If the plain_text is a space, add a space to the new_key.
        //  Else, copy the uppercased character of key_val
        new_key[i] = plain_text[i] == ' ' ? ' ' : toupper(key_val[j++]);
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
 * plain_text = "HELLOWORLD"
 * key = "EARTHEARTH"
 * encrypted_text = "FYWYPUICYE"
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
        if (islower(plain_text[i]))
        {
            // Encrypt lowercase letters
            // - 32 to convert it to an uppercase letter
            // + 97 to get the ASCII value of the encrypted letter
            encrypted_text[i] = (((plain_text[i] - 32) + key[i]) % MAX_ALPHA) + 'a';
        }
        else if (isupper(plain_text[i]))
        {
            // Encrypt uppercase letters
            // + 65 to get the ASCII value of the encrypted letter
            encrypted_text[i] = ((plain_text[i] + key[i]) % MAX_ALPHA) + 'A';
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
 * encrypted_text = "FYWYPUICYE"
 * key = "EARTH"
 * decrypted_text = "HELLOWORLD"
 */

char *decrypt(char cipher_text[], char key[])
{
    // Create an allocated space for the decrypted text to be returned.
    char *decrypted_text = (char *)calloc(strlen(cipher_text) + 1, sizeof(char));
    int i;

    // Traverse cipher_text
    for (i = 0; i < strlen(cipher_text); i++)
    {
        // Formula: (cipher_text[i] - key[i] + 26) % 26
        if (islower(cipher_text[i]))
        {
            // Decrypt lowercase letters
            // - 32 to convert it to an uppercase letter
            // + 97 to get the ASCII value of the encrypted letter
            decrypted_text[i] = (((cipher_text[i] - 32) - key[i] + MAX_ALPHA) % MAX_ALPHA) + 'a';
        }
        else if (isupper(cipher_text[i]))
        {
            // Decrypt uppercase letters
            // + 65 to get the ASCII value of the decrypted letter
            decrypted_text[i] = ((cipher_text[i] - key[i] + MAX_ALPHA) % MAX_ALPHA) + 'A';
        }
        else
        {
            // If the current character is not a letter, just copy it.
            decrypted_text[i] = cipher_text[i];
        }
    }

    return decrypted_text;
}
