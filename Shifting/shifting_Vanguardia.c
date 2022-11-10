#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALPHA 26
#define MAX_NUM 10
#define MAX_SIZE 255

void menu();
char *shift(char[], int);

int main()
{
    char plain_text[MAX_SIZE];
    int choice;
    int shift_val;

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

void menu()
{
    printf("[1] Encrypt\n");
    printf("[2] Decrypt\n");
    printf("[3] Exit\n");
    printf("\nSelect: ");
}

char *shift(char plain_text[], int shift_val)
{
    char *transformed_text = (char *)calloc(strlen(plain_text) + 1, sizeof(char));
    int i;

    for (i = 0; i < strlen(plain_text); i++)
    {
        if (islower(plain_text[i]))
        {
            transformed_text[i] = ((plain_text[i] + shift_val - 'a') % MAX_ALPHA) + 'a';
        }
        else if (isupper(plain_text[i]))
        {
            transformed_text[i] = ((plain_text[i] + shift_val - 'A') % MAX_ALPHA) + 'A';
        }
        else if (isdigit(plain_text[i]))
        {
            transformed_text[i] = ((plain_text[i] + shift_val - '0') % MAX_NUM) + '0';
        }
        else
        {
            transformed_text[i] = plain_text[i];
        }
    }

    return transformed_text;
}
