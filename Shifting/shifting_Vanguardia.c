#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALPHA 26
#define MAX_NUM 10
#define MAX_SIZE 255

int menu();
char *shift(char[], int);

int main()
{
    char plain_text[MAX_SIZE];
    int choice;
    int shift_val;

    do
    {
        menu();

        if (choice == 1)
        {
            printf("Input text: ");
            scanf("%[^\n]", &plain_text);
            fflush(stdin);

            printf("Input shift: ");
            scanf("%d", &shift_val);
            fflush(stdin);

            char *encrypted_text = shift(plain_text, shift_val);
            printf("Encrypted Text: %s", encrypted_text);
        }
        else if (choice == 2)
        {
            printf("Input text: ");
            scanf("%[^\n]", &plain_text);
            fflush(stdin);

            printf("Input shift: ");
            scanf("%d", &shift_val);
            fflush(stdin);

            char *decrypted_text = shift(plain_text, MAX_ALPHA - (shift_val % MAX_ALPHA));
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
 * This function will shift the characters of the plain text by the given shift value.
 *
 * @param plain_text The plain text to be encrypted or decrypted.
 * @param shift_val The shift value.
 *
 * @return transformed_text The encrypted or decrypted text.
 *
 * Example:
 *  plain_text = "Hello World"
 *  shift_val = 3
 *  transformed_text = "Khoor Zruog"
 *
 *  plain_text = "Khoor Zruog"
 *  shift_val = 23
 *  transformed_text = "Hello World"
 */

char *shift(char plain_text[], int shift_val)
{
    // Create an allocated memory for the transformed text.
    char *transformed_text = (char *)calloc(strlen(plain_text) + 1, sizeof(char));
    int i;

    // Loop through the plain text.
    for (i = 0; i < strlen(plain_text); i++)
    {
        if (islower(plain_text[i]))
        {
            // If the character is a lowercase letter.
            // Formula: (plain_text[i] + shift_val - 'a') % MAX_ALPHA + 'a'
            // Example: ('a' + 3 - 'a') % 26 + 'a' = 3 % 26 + 'a' = 3 + 'a' = 'd'
            transformed_text[i] = ((plain_text[i] + shift_val - 'a') % MAX_ALPHA) + 'a';
        }
        else if (isupper(plain_text[i]))
        {
            // If the character is an uppercase letter.
            // Formula: (plain_text[i] + shift_val - 'A') % MAX_ALPHA + 'A'
            // Example: ('A' + 3 - 'A') % 26 + 'A' = 3 % 26 + 'A' = 3 + 'A' = 'D'
            transformed_text[i] = ((plain_text[i] + shift_val - 'A') % MAX_ALPHA) + 'A';
        }
        else
        {
            // If the current character is not a letter, just copy it.
            transformed_text[i] = plain_text[i];
        }
    }

    return transformed_text;
}
