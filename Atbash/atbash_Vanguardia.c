#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 255

int menu();
char *abash(char[]);

int main()
{
    char text[MAX_SIZE];
    char filename[MAX_SIZE];
    int choice;

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
                printf("Error: Failed to opened the file.");
                break;
            }

            while (fgets(text, sizeof(text), file) != NULL)
            {
            }

            char *transformed_text = abash(text);
            printf("Result: %s", transformed_text);

            fclose(file);
        }
        else if (choice == 2)
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
    printf("Atbash Cryptography\n");
    printf("--------------------\n");
    printf("[1] Encrypt/Decrypt\n");
    printf("[2] Exit\n");
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
char *abash(char plain_text[])
{
    // Create an allocated memory for the transformed text.
    char *transformed_text = (char *)calloc(strlen(plain_text) + 1, sizeof(char));
    int i;

    // Loop through the plain text.
    for (i = 0; i < strlen(plain_text); i++)
    {
        // Transform the letter to its abashed form.
        // Example: a -> z, b -> y, c -> x, ..., z ->
        if (isalpha(plain_text[i]))
        {
            // If the letter is lowercase then return a lowercase letter
            // else return an uppercase letter
            transformed_text[i] = islower(plain_text[i]) ? 'z' - (plain_text[i] - 'a')
                                                         : 'Z' - (plain_text[i] - 'A');
        }
        else
        {
            // If the current character is not a letter, just copy it.
            transformed_text[i] = plain_text[i];
        }
    }

    return transformed_text;
}