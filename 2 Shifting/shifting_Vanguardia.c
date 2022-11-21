#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALPHA 26
#define MAX_SIZE 255

int menu();
char *shift(char[], int);
int getTextFromFile(char[], char[]);
void saveTextToFile(char[], char[]);

int main()
{
    do
    {
        int shift_val;
        char text[MAX_SIZE];

        int choice = menu();
        if (choice == 1)
        {
            int res = getTextFromFile(text, "plaintext");
            if (res)
            {
                printf("Enter shift value: ");
                scanf("%d", &shift_val);
                fflush(stdin);

                printf("Text: %s\n", text);

                char *encrypted_text = shift(text, shift_val);
                printf("\nCiphertext: %s\n", encrypted_text);

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
                printf("Enter shift value: ");
                scanf("%d", &shift_val);
                fflush(stdin);

                printf("Text: %s\n", text);
                char *decrypted_text = shift(text, MAX_ALPHA - (shift_val % MAX_ALPHA));
                printf("\nPlaintext: %s\n", decrypted_text);

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