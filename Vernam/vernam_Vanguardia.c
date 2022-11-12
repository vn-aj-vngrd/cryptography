#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 255
#define MAX_ALPHA 26

void menu();
char *generateKey(char[]);
char *vernam(char[], char[]);

int main()
{
    char text[MAX_SIZE] = "COH";
    char key_val[MAX_SIZE] = "SON";
    int choice = 1;

    do
    {
        // menu();

        // scanf("%d", &choice);
        // fflush(stdin);

        if (choice == 1)
        {
            // printf("Input text: ");
            // scanf("%[^\n]", &text);
            // fflush(stdin);

            // printf("Input key: ");
            // scanf("%[^\n]", &key_val);
            // fflush(stdin);

            // char *key = generateKey(key_val);
            // printf("Generated Key: %s\n", key);

            char *encrypted_text = vernam(text, key_val);
            // printf("Encrypted Text: %s", encrypted_text);
        }
        else if (choice == 2)
        {
            // printf("Input text: ");
            // scanf("%[^\n]", &text);
            // fflush(stdin);

            // printf("Input key: ");
            // scanf("%[^\n]", &key_val);
            // fflush(stdin);

            char *key = generateKey(key_val);
            printf("Generated Key: %s\n", key);

            char *decrypted_text = vernam(text, key);
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

        break;

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

char *generateKey(char key_val[])
{
    char *key = (char *)calloc(strlen(key_val) + 1, sizeof(char));

    return key;
}

char *vernam(char plain_text[], char key[])
{
    char *cipher_text = (char *)calloc((strlen(plain_text)) + 1, sizeof(char));

    int i, j, k = 0;
    for (i = 0; i < strlen(plain_text); i++)
    {
        int text_val = plain_text[i] - 'A';
        int key_val = key[i] - 'A';

        printf("%d\n%d", text_val, key_val);
        int cipher_val = (text_val ^ key_val) % MAX_ALPHA;
        printf("\n%d", cipher_val);

        cipher_text[k++] = cipher_val + 'A' -;
        printf(cipher_text);

        break;
    }

    return cipher_text;
}
