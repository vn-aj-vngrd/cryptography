#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 255

int menu();
char *vernam(char[], char[]);
char *generateOTP(char[]);
int validateOTP(char[], char[]);
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
                char otp[MAX_SIZE];
                int res = validateOTP(otp, text);

                if (res)
                {
                    printf("OTP: %s\n", otp);
                    printf("Text: %s\n", text);

                    char *transformed_text = vernam(text, otp);
                    printf("Result: %s\n", transformed_text);

                    saveTextToFile(transformed_text);
                }
                else
                {
                    printf("\nError: OTP is not valid.");
                }
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
                printf("OTP: %s\n", otp);

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
    printf("[2] Generate OTP\n");
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

char *vernam(char text[], char key[])
{
    char *transformed_text = (char *)calloc((strlen(text)) + 1, sizeof(char));
    int text_val, key_val, cipher_val;

    int i;
    for (i = 0; i < strlen(text); i++)
    {
        text_val = toupper(text[i]) - 'A';
        key_val = toupper(key[i]) - 'A';

        // Forumla: text_char XOR key_char
        cipher_val = text_val ^ key_val;
        transformed_text[i] = islower(text[i]) ? cipher_val + 'a' : cipher_val + 'A';
    }

    return transformed_text;
}

/*
 * This function generates a random key or OTP of the same length as the text.
 *
 * @param text The text to be used to generate the OTP.
 *
 * @return The generated OTP.
 *
 * Example:
 *  - text: Hello
 *  - otp:  World
 */

char *generateOTP(char text[])
{
    char *otp = (char *)calloc((strlen(text)) + 1, sizeof(char));
    
    int i;
    for (i = 0; i < strlen(text); i++)
    {
        otp[i] = rand() % 26 + 'A';
    }

    return otp;
}

/*
 * This function validates the OTP.
 *
 * @param otp The OTP to be validated.
 * @param text The text to be used to validate the OTP.
 *
 * @return 1 if the OTP is valid, 0 otherwise.
 *
 * Example:
 *  - text: Hello
 *  - otp:  World
 *  - otp is valid
 */

int validateOTP(char otp[], char text[])
{
    char filename[MAX_SIZE];

    printf("Enter OTP filename: ");
    scanf("%[^\n]", filename);
    fflush(stdin);

    FILE *file = fopen(strcat(filename, ".txt"), "r");
    if (file == NULL)
    {
        printf("Failed to open OTP file.");
        return 0;
    }

    fgets(otp, MAX_SIZE, file);
    fclose(file);

    if (strlen(otp) < strlen(text))
    {
        printf("OTP is too short.");
        return 0;
    }

    return 1;
}

/*
 * This function gets the text from a file.
 *
 * @param text The text to be read from the file.
 *
 * @return 1 if the text is read successfully, 0 otherwise.
 */

int getTextFromFile(char text[])
{
    char filename[MAX_SIZE];

    printf("Enter filename to open: ");
    scanf("%[^\n]", filename);
    fflush(stdin);

    FILE *file = fopen(strcat(filename, ".txt"), "r");
    if (!file)
    {
        return 0;
    }

    fgets(text, MAX_SIZE, file);
    fclose(file);

    return 1;
}

/*
 * This function saves the text to a file.
 *
 * @param text The text to be saved to the file.
 */

void saveTextToFile(char text[])
{
    char filename[MAX_SIZE];

    printf("Enter filename to save: ");
    scanf("%[^\n]", filename);
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