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
                char *transformed_text = vernam(text, key_val);
                printf("Encrypted Text: %s", transformed_text);
            }
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

    printf("Vernam OTP\n");
    printf("------------------\n");
    printf("[1] Generate OTP\n");
    printf("[2] Exit\n");
    printf("\nSelect: ");

    scanf("%d", &choice);
    fflush(stdin);

    return choice;
}

char *generateOTP(char text[], char key[])
{
    int i;
    char *otp = (char *)calloc((strlen(plain_text)) + 1, sizeof(char));

    return otp;
}