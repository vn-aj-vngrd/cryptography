#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALPHA 26
#define MAX_NUM 10
#define MAX_SIZE 255

void menu();
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
        menu();

        scanf("%d", &choice);
        fflush(stdin);

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

void menu()
{
    printf("[1] Encrypt\n");
    printf("[2] Decrypt\n");
    printf("[3] Exit\n");
    printf("\nSelect: ");
}

/*
 * Generate key by ordering the heirarchy of the letters.
 *
 * @param key_val
 *
 * @return key
 *
 * Example
 * key_val = "Lock"
 *  L->3
 *  o->4
 *  c->1
 *  k->2
 * key = "3412"
 */

char *generateKey(char key_val[])
{
    char *key = (char *)calloc(strlen(key_val) + 1, sizeof(char));
    int i, j, k = 0;

    for (i = 0; i < strlen(key_val); i++)
    {
        for (j = 0; j < strlen(key_val); j++)
        {
            if (key_val[i] > key_val[j])
            {
                k++;
            }
        }
        key[i] = k + '1';
        k = 0;
    }

    return key;
}

/*
 * Encrypt the text using the key.
 *
 * @param text
 * @param key
 *
 * @return encrypted_text
 *
 * Example
 * text = "Hello World"
 * key = "3412"
 * encrypted_text = "lWdlo_Hore_l"
 */

char *encrypt(char plain_text[], char key[])
{
    int row = strlen(plain_text) / strlen(key);
    if (strlen(plain_text) % strlen(key) != 0)
        row++;
    int col = strlen(key);

    char *cipher_text = (char *)calloc((row * col) + 1, sizeof(char));
    char matrix[row][col];
    int i, j, k;

    k = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            if (k < strlen(plain_text))
            {
                matrix[i][j] = plain_text[k] == ' ' ? '_' : plain_text[k];
                k++;
            }
            else
            {
                matrix[i][j] = '_';
            }
        }
    }

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    k = 0;
    for (i = 0; i < col; i++)
    {
        for (j = 0; j < row; j++)
        {
            cipher_text[k] = matrix[j][key[i] - '1'];
            k++;
        }
    }

    return cipher_text;
}

/*
 * Decrypt the text using the key.
 *
 * @param text
 * @param key
 *
 * @return decrypted_text
 *
 * Example
 * text = "lWdlo_Hore_l"
 * key = "3412"
 * decrypted_text = "Hello_World_"
 */

char *decrypt(char cipher_text[], char key[])
{
    int row = strlen(cipher_text) / strlen(key);
    int col = strlen(key);

    char *plain_text = (char *)calloc((row * col) + 1, sizeof(char));
    char matrix[row][col];
    int i, j, k;

    k = 0;
    for (i = 0; i < col; i++)
    {
        for (j = 0; j < row; j++)
        {
            matrix[j][key[i] - '1'] = cipher_text[k];
            k++;
        }
    }

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    k = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            plain_text[k] = matrix[i][j];
            k++;
        }
    }

    return plain_text;
}