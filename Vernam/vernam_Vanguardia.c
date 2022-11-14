#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 255

int menu();
char *vernam(char[], char[]);

int main()
{
    char text[MAX_SIZE];
    char key_val[MAX_SIZE];
    int choice;

    do
    {
        choice = menu();

        if (choice == 1)
        {
            printf("Input text: ");
            scanf("%[^\n]", &text);
            fflush(stdin);

            printf("Input key: ");
            scanf("%[^\n]", &key_val);
            fflush(stdin);

            if (strlen(key_val) < strlen(text))
            {
                printf("Error: The key must be of the same length or greater as the text.");
            }
            else
            {
                char *encrypted_text = vernam(text, key_val);
                printf("Encrypted Text: %s", encrypted_text);
            }
        }
        else if (choice == 2)
        {
            printf("Input text: ");
            scanf("%[^\n]", &text);
            fflush(stdin);

            printf("Input key: ");
            scanf("%[^\n]", &key_val);
            fflush(stdin);

            if (strlen(key_val) < strlen(text))
            {
                printf("Error: The key must be of the same length or greater as the text.");
            }
            else
            {
                char *decrypted_text = vernam(text, key_val);
                printf("Decrypted Text: %s", decrypted_text);
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

    printf("[1] Encrypt\n");
    printf("[2] Decrypt\n");
    printf("[3] Exit\n");
    printf("\nSelect: ");

    scanf("%d", &choice);
    fflush(stdin);

    return choice;
}

/*
 * This function encrypts and decrypts the text using the Vernam Cipher.
 * The key must be of the same length or greater as the text.
 *
 * @param text The text to be encrypted or decrypted.
 * @param key The key to be used for encryption or decryption.
 *
 * @return The encrypted or decrypted text.
 *
 * Example:
 *  - Encrypt
 *      text: Hello
 *      key:  World
 *      encrypted_text: Rk{an
 *
 *  - Decrypt
 *      text: Rk{an
 *      key:  World
 *      decrypted_text: Hello
 */

char *vernam(char plain_text[], char key[])
{
    char *cipher_text = (char *)calloc((strlen(plain_text)) + 1, sizeof(char));
    int text_val, key_val, cipher_val;

    int i;
    for (i = 0; i < strlen(plain_text); i++)
    {
        text_val = toupper(plain_text[i]) - 'A';
        key_val = toupper(key[i]) - 'A';

        cipher_val = text_val ^ key_val;
        cipher_text[i] = islower(plain_text[i]) ? cipher_val + 'a' : cipher_val + 'A';
    }

    return cipher_text;
}
