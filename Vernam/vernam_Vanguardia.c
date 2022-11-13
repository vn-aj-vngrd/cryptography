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
    char text[MAX_SIZE] = "KEKXD";
    char key_val[MAX_SIZE] = "DAZMP";
    int choice = 2;

    do
    {
        //choice =  menu();

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

            char *encrypted_text = encrypt(text, key_val);
            printf("\n\nEncrypted Text: %s", encrypted_text);
        }
        else if (choice == 2)
        {
            // printf("Input text: ");
            // scanf("%[^\n]", &text);
            // fflush(stdin);

            // printf("Input key: ");
            // scanf("%[^\n]", &key_val);
            // fflush(stdin);

            // char *key = generateKey(key_val);
            // printf("Generated Key: %s\n", key);

            char *decrypted_text = decrypt(text, key_val);
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

int menu()
{
    printf("[1] Encrypt\n");
    printf("[2] Decrypt\n");
    printf("[3] Exit\n");
    printf("\nSelect: ");

    // scanf("%d", &choice);
    // fflush(stdin);
}

char *generateKey(char key_val[])
{
    char *key = (char *)calloc(strlen(key_val) + 1, sizeof(char));

    return key;
}

char *encrypt(char plain_text[], char key[])
{
    char *cipher_text = (char *)calloc((strlen(plain_text)) + 1, sizeof(char));

    int i, j, k = 0;
    for (i = 0; i < strlen(plain_text); i++)
    {
        if (isalpha(plain_text[i]))
        {
            int text_val = plain_text[i] - 'A';
            int key_val = key[i] - 'A';

            int sum = text_val + key_val;
            if (sum >= MAX_ALPHA)
                sum -= MAX_ALPHA;

            cipher_text[i] = sum + 'A';
        }
    }

    return cipher_text;
}

char *decrypt(char cipher_text[], char key[])
{
    char *plain_text = (char *)calloc((strlen(cipher_text)) + 1, sizeof(char));

    int i, j, k = 0;
    for (i = 0; i < strlen(cipher_text); i++)
    {
        if (isalpha(cipher_text[i]))
        {
            int text_val = cipher_text[i] - 'A';
            int key_val = key[i] - 'A';

            int sum = text_val - key_val;
            if (sum < 0)
                sum += MAX_ALPHA;

            plain_text[i] = sum + 'A';
        }
    }

    return plain_text;
}