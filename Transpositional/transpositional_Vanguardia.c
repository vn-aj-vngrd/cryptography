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
    char filename[MAX_SIZE];
    char key_val[MAX_SIZE];
    int choice;

    do
    {
        choice = menu();

        if (choice == 1)
        {
            printf("Enter filename: ");
            scanf("%[^\n]", &filename);
            fflush(stdin);

            FILE *file = fopen(strcat(filename, ".txt"), "r");
            if (file == NULL)
            {
                printf("Error: Failed to open the file.");
                break;
            }

            while (fgets(text, sizeof(text), file) != NULL)
            {
            }

            printf("Input key: ");
            scanf("%[^\n]", &key_val);
            fflush(stdin);

            char *key = generateKey(key_val);
            printf("Generated Key: %s\n", key);

            char *encrypted_text = encrypt(text, key);
            printf("Encrypted Text: %s", encrypted_text);

            fclose(file);
        }
        else if (choice == 2)
        {
            printf("Enter filename: ");
            scanf("%[^\n]", &filename);
            fflush(stdin);

            FILE *file = fopen(strcat(filename, ".txt"), "r");
            if (file == NULL)
            {
                printf("Error: Failed to open the file.");
                break;
            }

            while (fgets(text, sizeof(text), file) != NULL)
            {
            }

            printf("Input key: ");
            scanf("%[^\n]", &key_val);
            fflush(stdin);

            char *key = generateKey(key_val);
            printf("Generated Key: %s\n", key);

            char *decrypted_text = decrypt(text, key);
            printf("Decrypted Text: %s", decrypted_text);

            fclose(file);
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

    printf("Transpositional Cryptograph\n");
    printf("---------------------------\n");
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
 * key_val = "Earth"
 *  E->2
 *  a->1
 *  r->4
 *  t->5
 *  h->3
 * key = "21453"
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
            if (toupper(key_val[i]) > toupper(key_val[j]))
            {
                k++;
            }
        }
        // Convert the key value to a digit character and append it to the key.
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
 * key_val = "Earth"
 * generated_key: 21453
 * encrypted_text = "eW!H_dol_lo_lr_"
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
        // Get the index position of the key that corresponds to the iterator's value
        int key_idx;
        for (j = 0; strlen(key); j++)
        {
            if (key[j] == i + '1')
            {
                key_idx = j;
                break;
            }
        }

        // Get the row and column of the matrix that corresponds to the iterator's value and key index.
        for (j = 0; j < row; j++)
        {
            cipher_text[k] = matrix[j][key_idx];
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
 * text = "eW!H_dol_lo_lr_"
 * key_val = "Earth"
 * generated_key: 21453
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
    int i, j, k, l;

    // Initialize the matrix with the cipher text.
    k = 0;
    for (i = 0; i < col; i++)
    {
        // Get the index position of the key that corresponds to the iterator's value
        int key_idx;
        for (j = 0; strlen(key); j++)
        {
            if (key[j] == i + '1')
            {
                key_idx = j;
                break;
            }
        }

        // Get the row and column of the matrix that corresponds to the iterator's value and key index.
        for (j = 0; j < row; j++)
        {
            matrix[j][key_idx] = cipher_text[k];
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
            plain_text[k] = matrix[i][j] == '_' ? ' ' : matrix[i][j];
            k++;
        }
    }

    return plain_text;
}