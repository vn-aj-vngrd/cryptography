#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void menu();
char *abash(char[]);

int main()
{
    char plain_text[999];
    int choice;

    do
    {
        menu();

        printf("\nSelect: ");
        scanf("%d", &choice);
        fflush(stdin);

        if (choice == 1)
        {
            printf("Input text: ");
            scanf("%[^\n]", &plain_text);
            fflush(stdin);

            char *encrypted_text = abash(plain_text);
            printf("Result: %s", encrypted_text);
        }
        else if (choice == 2)
        {
            printf("Input text: ");
            scanf("%[^\n]", &plain_text);
            fflush(stdin);

            char *decrypted_text = abash(plain_text);
            printf("Result: %s", decrypted_text);
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
}

char *abash(char plain_text[])
{
    char *encrypted_text = (char *)calloc(strlen(plain_text), sizeof(char));
    int i;

    for (i = 0; i < strlen(plain_text); i++)
    {
        if (islower(plain_text[i]))
        {
            encrypted_text[i] = 'z' - (plain_text[i] - 'a');
        }
        else if (isupper(plain_text[i]))
        {
            encrypted_text[i] = 'Z' - (plain_text[i] - 'A');
        }
        else
        {
            encrypted_text[i] = plain_text[i];
        }
    }

    return encrypted_text;
}