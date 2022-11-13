#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 255
#define MAX_ALPHA 26

int menu();
char *generateKey(char[]);
char *encrypt(char[], char[]);
char *decrypt(char[], char[]);

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

            char *key = generateKey(key_val);
            printf("Generated Key: %s\n", key);

            char *encrypted_text = encrypt(text, key);
            printf("Encrypted Text: %s", encrypted_text);
        }
        else if (choice == 2)
        {
            printf("Input text: ");
            scanf("%[^\n]", &text);
            fflush(stdin);

            printf("Input key: ");
            scanf("%[^\n]", &key_val);
            fflush(stdin);

            char *key = generateKey(key_val);
            printf("Generated Key: %s\n", key);

            char *decrypted_text = decrypt(text, key);
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

int menu()
{
    int choice;

    printf("[1] Encrypt\n");
    printf("[2] Decrypt\n");
    printf("[3] Exit\n");
    printf("\nSelect: ");

    scanf("%d", &choice);
    fflush(stdin);

    return choice;
}

char *generateKey(char key_val[])
{
    char *key = (char *)calloc(strlen(key_val) + 1, sizeof(char));
    int i;

    for (i = 0; i < strlen(key_val); i++)
    {
        key[i] = toupper(key_val[i]);
    }

    return key;
}

char *encrypt(char plain_text[], char key[])
{
    char *cipher_text = (char *)calloc((strlen(plain_text)) + 1, sizeof(char));
    int text_val, key_val, sum;

    int i, j;
    for (i = 0; i < strlen(plain_text); i++)
    {
        if (isalpha(plain_text[i]))
        {
            text_val = toupper(plain_text[i]) - 'A';
            key_val = toupper(key[i]) - 'A';

            sum = text_val + key_val;
            if (sum > MAX_ALPHA - 1)
                sum -= MAX_ALPHA;

            cipher_text[i] = islower(plain_text[i]) ? tolower(sum + 'A') : sum + 'A';
        }
        else
        {
            cipher_text[i] = plain_text[i];
        }
    }

    return cipher_text;
}

char *decrypt(char cipher_text[], char key[])
{
    char *plain_text = (char *)calloc((strlen(cipher_text)) + 1, sizeof(char));
    int text_val, key_val, diff;

    int i, j;
    for (i = 0; i < strlen(cipher_text); i++)
    {
        if (isalpha(cipher_text[i]))
        {
            text_val = toupper(cipher_text[i]) - 'A';
            key_val = toupper(key[i]) - 'A';

            diff = text_val - key_val;
            if (diff < 0)
                diff += MAX_ALPHA;

            plain_text[i] = islower(cipher_text[i]) ? tolower(diff + 'A') : diff + 'A';
        }
        else
        {
            plain_text[i] = cipher_text[i];
        }
    }

    return plain_text;
}