#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALPHA 26
#define MAX_SIZE 255

int menu();
char *encrypt(char[], char[]);
char *decrypt(char[], char[]);
int getTextFromFile(char[]);
void saveTextToFile(char[]);

int main()
{
    do
    {
        char text[MAX_SIZE];

        int choice = menu();
        if (choice == 1)
        {
            int res = getTextFromFile(text);
            if (res)
            {
                char *key = generateKey(text);
                printf("Generated Key: %s\n", key);

                printf("Text: %s\n", text);

                char *encrypted_text = encrypt(text, key);
                printf("Encrypted Text: %s\n", encrypted_text);

                saveTextToFile(encrypted_text);
            }
            else
            {
                printf("Error: Failed to read the file.");
            }
        }
        else if (choice == 2)
        {
            int res = getTextFromFile(text);
            if (res)
            {
                char *key = generateKey(text);
                printf("Generated Key: %s\n", key);

                printf("Text: %s\n", text);

                char *decrypted_text = decrypt(text, key);
                printf("Decrypted Text: %s\n", decrypted_text);

                saveTextToFile(decrypted_text);
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

    printf("Polyalphabetic Cryptograph\n");
    printf("-------------------------\n");
    printf("[1] Encrypt\n");
    printf("[2] Decrypt\n");
    printf("[3] Exit\n");
    printf("\nSelect: ");

    scanf("%d", &choice);
    fflush(stdin);

    return choice;
}


char *encrypt(char plain_text[], char key[])
{
    // Create an allocated space for the encrypted text to be returned.
    char *encrypted_text = (char *)calloc(strlen(plain_text) + 1, sizeof(char));

    return encrypted_text;
}



char *decrypt(char cipher_text[], char key[])
{
    // Create an allocated space for the decrypted text to be returned.
    char *decrypted_text = (char *)calloc(strlen(cipher_text) + 1, sizeof(char));

    return decrypted_text;
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
    scanf("%[^\n]", &filename);
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