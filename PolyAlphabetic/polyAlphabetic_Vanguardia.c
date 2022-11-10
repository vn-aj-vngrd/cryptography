#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALPHA 26
#define MAX_NUM 10
#define MAX_SIZE 255

void menu();
char *generateKey(char[], char[]);
char *encrypt(char[], char[]);
char *decrypt(char[], char[]);

int main()
{
    char plain_text[MAX_SIZE];
    char key_val[MAX_SIZE];
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

            printf("Input key: ");
            scanf("%[^\n]", &key_val);
            fflush(stdin);

            char *new_key = generateKey(plain_text, key_val);

            char *encrypted_text = encrypt(plain_text, new_key);
            printf("Encrypted Text: %s", encrypted_text);
        }
        else if (choice == 2)
        {
            printf("Input text: ");
            scanf("%[^\n]", &plain_text);
            fflush(stdin);

            printf("Input key: ");
            scanf("%[^\n]", &key_val);
            fflush(stdin);

            char *new_key = generateKey(plain_text, key_val);

            char *decrypted_text = decrypt(plain_text, new_key);
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

char *generateKey(char plain_text[], char key_val[])
{
    int i, j;
    char *new_key = (char *)calloc((strlen(plain_text) + 1), sizeof(char));

    for (i = 0, j = 0; i < strlen(plain_text); ++i, ++j)
    {
        if (j == strlen(key_val))
            j = 0;

        new_key[i] = key_val[j];
    }

    return new_key;
}

char *encrypt(char plain_text[], char key[])
{
    char *encrypted_text = (char *)calloc(strlen(plain_text) + 1, sizeof(char));
    int i;

    for (i = 0; i < strlen(plain_text); i++)
    {

        if (islower(plain_text[i]))
        {
            encrypted_text[i] = ((plain_text[i] + key[i]) % MAX_ALPHA) + 'a';
        }
        else if (isupper(plain_text[i]))
        {

            encrypted_text[i] = ((plain_text[i] + key[i]) % MAX_ALPHA) + 'A';
        }
        else
        {
            encrypted_text[i] = plain_text[i];
        }
    }
    return encrypted_text;
}

char *decrypt(char plain_text[], char key[])
{
    char *decrypted_text = (char *)calloc(strlen(plain_text) + 1, sizeof(char));
    int i;

    for (i = 0; i < strlen(plain_text); i++)
    {
        if (isalpha(plain_text[i]))
        {
            if (isupper(plain_text[i]))
            {
                decrypted_text[i] = ((plain_text[i] - key[i] + MAX_ALPHA) % MAX_ALPHA) + 'A';
            }
            else
            {
                decrypted_text[i] = ((plain_text[i] - key[i] + MAX_ALPHA) % MAX_ALPHA) + 'a';
            }
        }
        else if (isdigit(plain_text[i]))
        {
            decrypted_text[i] = ((plain_text[i] - key[i] + MAX_NUM) % MAX_NUM) + '0';
        }
        else
        {
            decrypted_text[i] = plain_text[i];
        }
    }

    return decrypted_text;
}
