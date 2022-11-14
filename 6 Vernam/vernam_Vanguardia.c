#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 255

int menu();
char *vernam(char[], char[]);
char *generateOTP(char[]);
int validateOTP();
int getTextFromFile(char[]);
void saveTextToFile(char[]);

int main()
{
    do
    {
        char text[MAX_SIZE];

        int choice = menu();
        if (choice == 1)
        {
            int res = getTextFromFile(text);
            if (res)
            {
                char *transformed_text = vernam(text, key_val);
                printf("Encrypted Text: %s", transformed_text);
            }
            else
            {
                printf("Error: Failed to read the file.");
            }
        }
        else if (choice == 2)
        {
            int res = getTextFromFile(text);
            if (res)
            {
                char *otp = generateOTP(text);
                printf("OTP: %s", otp);

                saveTextToFile(otp);
            }
            else
            {
                printf("Error: Failed to read the file.");
            }
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

    printf("Vernam Cryptograph\n");
    printf("-------------------\n");
    printf("[1] Encrypt/Decrypt\n");
    printf("[2] Generate Key\n");
    printf("[3] Exit\n");
    printf("\nSelect: ");

    scanf("%d", &choice);
    fflush(stdin);

    return choice;
}

/*
 * This function encrypts and decrypts the text using bitwise XOR.
 * The key must be of the same length or greater as the text.
 *
 * @param text The text to be encrypted or decrypted.
 * @param key The key to be used for encryption or decryption.
 *
 * @return The encrypted or decrypted text.
 *
 * Example:
 *  - Encrypt
 *      text: Hello
 *      key:  World
 *      encrypted_text: Rk{an
 *
 *  - Decrypt
 *      text: Rk{an
 *      key:  World
 *      decrypted_text: Hello
 */

char *vernam(char plain_text[], char key[])
{
    char *transformed_text = (char *)calloc((strlen(plain_text)) + 1, sizeof(char));
    int text_val, key_val, cipher_val;

    int i;
    for (i = 0; i < strlen(plain_text); i++)
    {
        text_val = toupper(plain_text[i]) - 'A';
        key_val = toupper(key[i]) - 'A';

        cipher_val = text_val ^ key_val;
        transformed_text[i] = islower(plain_text[i]) ? cipher_val + 'a' : cipher_val + 'A';
    }

    return transformed_text;
}

char *generateOTP(char text[])
{
    char *key = (char *)calloc((strlen(text)) + 1, sizeof(char));
    int i;
    for (i = 0; i < strlen(text); i++)
    {
        key[i] = rand() % 26 + 'A';
    }

    return key;
}

int validateOTP()
{
    char filename[MAX_SIZE];
    printf("Enter OTP filename: ");
    scanf("%[^\n]", &otp);
}

int getTextFromFile(char text[])
{
    char filename[MAX_SIZE];

    printf("Enter filename to open: ");
    scanf("%[^\n]", &filename);
    fflush(stdin);

    FILE *file = fopen(strcat(filename, ".txt"), "r");
    if (!file)
    {
        return 0;
    }

    while (fgets(text, MAX_SIZE, file) != NULL)
    {
    }

    fclose(file);

    return 1;
}

void saveTextToFile(char text[])
{
    char filename[MAX_SIZE];

    printf("Enter filename to save: ");
    scanf("%[^\n]", &filename);
    fflush(stdin);

    FILE *file = fopen(strcat(filename, ".txt"), "w");
    if (!file)
    {
        printf("Failed to save file.");
    }

    fprintf(file, "%s", text);
    fclose(file);

    printf("File saved successfully.");
}