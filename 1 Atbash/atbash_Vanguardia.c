#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 255

int menu();
char *atbash(char[]);
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
                printf("Text: %s\n", text);
                char *transformed_text = atbash(text);
                printf("\nCiphertext: %s\n", transformed_text);

                saveTextToFile(transformed_text, "ciphertext");
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
                printf("Text: %s\n", text);
                char *transformed_text = atbash(text);
                printf("\nPlaintext: %s\n", transformed_text);

                saveTextToFile(transformed_text, "plaintext");
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

    printf("------------------\n");
    printf("Atbash Cryptograph\n");
    printf("------------------\n");
    printf("[1] Encrypt\n");
    printf("[2] Decrypt\n");
    printf("[3] Exit\n");
    printf("\nSelect: ");

    scanf("%d", &choice);
    fflush(stdin);

    return choice;
}

/*
 * This function will transform the given text to its abashed form.
 *
 * @param plain_text
 * @return transformed_text
 *
 * Example:
 * Input: Hello World!
 * Output: Svool Dliow!
 */

char *atbash(char text[])
{
    // Create an allocated memory for the transformed text.
    char *transformed_text = (char *)calloc(strlen(text) + 1, sizeof(char));
    int i;

    // Loop through the plain text.
    for (i = 0; i < strlen(text); i++)
    {
        // Transform the letter to its abashed form.
        // Example: a -> z, b -> y, c -> x, ..., z ->
        if (isalpha(text[i]))
        {
            // If the letter is lowercase then return a lowercase letter
            // else return an uppercase letter
            transformed_text[i] = islower(text[i]) ? 'z' - (text[i] - 'a')
                                                   : 'Z' - (text[i] - 'A');
        }
        else
        {
            // If the current character is not a letter, just copy it.
            transformed_text[i] = text[i];
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