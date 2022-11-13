#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 255

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
            // If the current letter is greater than the next letter
            // then increment the key value.
            if (key_val[i] > key_val[j])
            {
                k++;
            }
        }
        // Convert the key value to a character and append it to the key.
        key[i] = k + '1';

        // Reset the key value.
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
    // If the length of the plain text is not divisible by the length of the key, add 1 to the row.
    if (strlen(plain_text) % strlen(key) != 0)
        row++;

    int col = strlen(key);

    // Create an allocated memory for the cipher text.
    char *cipher_text = (char *)calloc((row * col) + 1, sizeof(char));

    // Create a 2D array to store the plain text.
    char matrix[row][col];
    int i, j, k;

    // Initialize the matrix with the plain text.
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

    // Display the matrix.
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    // Encrypt the plain text.
    k = 0;
    for (i = 0; i < col; i++)
    {
        for (j = 0; j < row; j++)
        {
            // Get the column number of the key.
            // Store the value to the cipher text.
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

    // Create an allocated memory for the plain text.
    char *plain_text = (char *)calloc((row * col) + 1, sizeof(char));

    // Create a 2D array to store the cipher text.
    char matrix[row][col];
    int i, j, k;

    // Initialize the matrix with the cipher text.
    k = 0;
    for (i = 0; i < col; i++)
    {
        for (j = 0; j < row; j++)
        {
            // Get the column number of the key.
            // Store the value to the matrix.
            matrix[j][key[i] - '1'] = cipher_text[k];
            k++;
        }
    }

    // Display the matrix.
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    // Decrypt the cipher text.
    k = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            // Store the value to the plain text.
            plain_text[k] = matrix[i][j];
            k++;
        }
    }

    return plain_text;
}