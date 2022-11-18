#include <stdio.h>

#include "functions.c"

int main()
{
  do
  {
    char text[MAX_SIZE];
    char key[MAX_SIZE];

    int choice = menu();

    if (choice == 1)
    {
      int r = getTextFromFile(text, "plaintext");
      printf("Text: %s\n", text);

      if (r)
      {
        char *cipher_text = encrypt(text);
        printf("\n\nCiphertext: %s\n", cipher_text);
        saveTextToFile(cipher_text, "ciphertext");
      }
      else
      {
        printf("Error: File not found!\n");
      }
    }

    else if (choice == 2)
    {
      int r1 = getTextFromFile(text, "ciphertext");
      if (r1)
      {
        printf("Ciphertext: %s\n", text);

        int r2 = getTextFromFile(key, "key");
        if (r2)
        {
          printf("Key: %s\n\n", key);

          char *plain_text = decrypt(text, key);
          printf("Plaintext: %s\n", plain_text);
          saveTextToFile(plain_text, "plaintext");
        }
        else
        {
          printf("Error: File not found!\n");
        }
      }
      else
      {
        printf("Error: File not found!\n");
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
