#include <stdio.h>
#include "functions/functions.c"

int main()
{
    do
    {
        int i;
        int choice = menu();

        if (choice == 1)
        {
            char plaintext_str[MAX_SIZE];
            int r = getTextFromFile(plaintext_str, "plaintext");

            if (r)
            {
                // Display Plaintext in letters
                printf("Plaintext: %s\n", plaintext_str);

                // Display Plaintext in numbers
                int *plaintext_num = formatTextInNum(plaintext_str);
                printf("Plaintext in numbers: ");
                displayNumText(plaintext_num);

                // Encryption Process
                char *ciphertext = encrypt(plaintext_str);
                printf("\n\nCiphertext: %s\n", ciphertext);

                // Save ciphertext to file
                saveTextToFile(ciphertext, "ciphertext");
            }
            else
            {
                printf("Error: Failed to read the file.");
            }
        }
        else if (choice == 2)
        {
            char ciphertext_str[MAX_SIZE];
            int r1 = getTextFromFile(ciphertext_str, "ciphertext");

            if (r1)
            {
                // Display Ciphertext in letters
                printf("Ciphertext: %s\n", ciphertext_str);

                // Display Ciphertext in numbers
                int *ciphertext_num = formatTextInNum(ciphertext_str);
                printf("Ciphertext in numbers: ");
                displayNumText(ciphertext_num);
                printf("\n\n");

                char key_str[MAX_SIZE];
                int r2 = getTextFromFile(key_str, "key");
                if (r2)
                {
                    // Display Key
                    printf("Key: %s\n", key_str);

                    // Decryption Process
                    char *plaintext = decrypt(ciphertext_str, key_str);
                    printf("\nPlaintext: %s\n", plaintext);

                    // Save plaintext to file
                    saveTextToFile(plaintext, "plaintext");
                }
                else
                {
                    printf("Error: Failed to read the file.");
                }
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