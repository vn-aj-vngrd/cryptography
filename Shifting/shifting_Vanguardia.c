#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALPHA 26
#define MAX_SIZE 255

int menu();
char *shift(char[], int);

int main()
{
    char text[MAX_SIZE];
    char filename[MAX_SIZE];
    int choice;
    int shift_val;

    do
    {
        choice = menu();

        if (choice == 1)
        {
            printf("Enter filename: ");
            scanf("%[^\n]", &filename);
            fflush(stdin);

            FILE *file = fopen(strcat(filename, ".txt"), "r");
            if (file == NULL)
            {
                printf("Error: Failed to open the file.");
                break;
            }

            while (fgets(text, sizeof(text), file) != NULL)
            {
            }

            printf("Enter shift value: ");
            scanf("%d", &shift_val);
            fflush(stdin);

            char *encrypted_text = shift(text, shift_val);
            printf("Encrypted Text: %s", encrypted_text);

            fclose(file);
        }
        else if (choice == 2)
        {

            printf("Enter filename: ");
            scanf("%[^\n]", &filename);
            fflush(stdin);

            FILE *file = fopen(strcat(filename, ".txt"), "r");
            if (file == NULL)
            {
                printf("Error: Failed to open the file.");
                break;
            }

            while (fgets(text, sizeof(text), file) != NULL)
            {
            }

            printf("Enter shift value: ");
            scanf("%d", &shift_val);
            fflush(stdin);

            char *decrypted_text = shift(text, MAX_ALPHA - (shift_val % MAX_ALPHA));
            printf("Decrypted Text: %s", decrypted_text);

            fclose(file);
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

    printf("Shifting Cryptograph\n");
    printf("--------------------\n");
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
 * - Encrypt
 *      plain_text = "Hello World"
 *      shift_val = 3
 *      transformed_text = "Khoor Zruog"
 *
 * - Decrypt
 *      plain_text = "Khoor Zruog"
 *      shift_val = 3
 *      transformed_text = "Hello World"
 */

char *shift(char plain_text[], int shift_val)
{
    // Create an allocated memory for the transformed text.
    char *transformed_text = (char *)calloc(strlen(plain_text) + 1, sizeof(char));
    int i;

    // Loop through the text.
    for (i = 0; i < strlen(plain_text); i++)
    {
        // Formula: (x + n) mod 26
        if (isalpha(plain_text[i]))
        {
            transformed_text[i] = islower(plain_text[i]) ? ((plain_text[i] + shift_val - 'a') % MAX_ALPHA) + 'a'
                                                         : ((plain_text[i] + shift_val - 'A') % MAX_ALPHA) + 'A';
        }
        else
        {
            // If the current character is not a letter, just copy it.
            transformed_text[i] = plain_text[i];
        }
    }

    return transformed_text;
}
