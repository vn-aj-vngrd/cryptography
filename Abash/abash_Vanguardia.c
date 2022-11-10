#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 255

void menu();
char *abash(char[]);

int main()
{
    char plain_text[MAX_SIZE];
    int choice;

    do
    {
        menu();

        scanf("%d", &choice);
        fflush(stdin);

        if (choice == 1)
        {
            printf("Input text: ");
            scanf("%[^\n]", &plain_text);
            fflush(stdin);

            char *transformed_text = abash(plain_text);
            printf("Result: %s", transformed_text);
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

void menu()
{
    printf("[1] Start\n");
    printf("[2] Exit\n");
    printf("\nSelect: ");
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
        // Check if the current character is a letter.
        if (islower(plain_text[i]))
        {
            // Transform the letter to its abashed form.
            // Example: a -> z, b -> y, c -> x, ..., z -> a
            transformed_text[i] = 'z' - (plain_text[i] - 'a');
        }
        else if (isupper(plain_text[i]))
        {
            // Transform the letter to its abashed form.
            // Example: A -> Z, B -> Y, C -> X, ..., Z -> A
            transformed_text[i] = 'Z' - (plain_text[i] - 'A');
        }
        else
        {
            // If the current character is not a letter, just copy it.
            transformed_text[i] = plain_text[i];
        }
    }

    return transformed_text;
}