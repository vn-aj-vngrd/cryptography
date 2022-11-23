#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Utilize a library to store and manipulate large numbers
#include "bn.c"

#define MAX_ALPHA 26
#define MAX_SIZE 256
#define MAX_D 2048

char *encrypt(char plaintext[]);
char *decrypt(char ciphertext[], char key[]);

int calculateE(int n, int t);
int calculateD(int e, int t);

int *formatTextInNum(char text[]);

int getTextFromFile(char text[], char type[]);
void saveTextToFile(char text[], char type[]);
void displayNumText(int text[]);
int menu();

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

/************************************************************************************************************************
 * Main Functions (Encypt/Decrypt)
 ************************************************************************************************************************/

/*
 * Encrypt the plaintext
 *
 * @param plaintext
 *
 * @return ciphertext
 */

char *encrypt(char plaintext[])
{
  char *ciphertext = (char *)calloc(strlen(plaintext) + 1, sizeof(char));

  // Two prime numbers
  int p;
  int q;

  printf("\n\nEnter first prime number (p): ");
  scanf("%d", &p);
  fflush(stdin);

  printf("Enter second prime number (q): ");
  scanf("%d", &q);
  fflush(stdin);

  // Let N = p * q
  int n = p * q;

  // Get the Euler Totient
  int t = (p - 1) * (q - 1);

  // (e * d) mod t = 1
  int e = calculateE(n, t);
  int d = calculateD(e, t);

  // For debugging purpose
  // printf("e: %d\nd: %d\nt: %d\nn: %d\n", e, d, t, n);

  // delimiter
  char delim = ',';

  int delim_size = 1;
  int e_size = floor(log10(abs(e))) + 1;
  int d_size = floor(log10(abs(d))) + 1;
  int n_size = floor(log10(abs(n))) + 1;

  int private_key_size = d_size + delim_size + n_size + 1;
  int public_key_size = e_size + delim_size + n_size + 1;

  // Save private key
  char *private_key = (char *)calloc(private_key_size, sizeof(char));
  sprintf(private_key, "%d%c%d", d, delim, n);
  printf("\nPrivate Key: %s\n", private_key);
  saveTextToFile(private_key, "private key");

  // Save public key
  char *public_key = (char *)calloc(public_key_size, sizeof(char));
  sprintf(public_key, "%d%c%d", e, delim, n);
  printf("\n\nPublic Key: %s\n", public_key);
  saveTextToFile(public_key, "public key");

  // Declare bignum variables
  // M -> plaintext
  // C -> ciphertext
  // E -> public key 1, exponent
  // N -> public key 2, modulus
  struct bn M, C, E, N;

  // Initialize bignum variables
  bignum_init(&M);
  bignum_init(&C);
  bignum_init(&E);
  bignum_init(&N);

  // Encryption Process
  int i;
  for (i = 0; i < strlen(plaintext); i++)
  {
    if (isalpha(plaintext[i]))
    {
      // Assign bignum
      bignum_from_int(&M, toupper(plaintext[i]) - 'A' + 1);
      bignum_from_int(&E, e);
      bignum_from_int(&N, n);

      // Calculate C = (M ^ E) % N
      bignum_pow_mod(&M, &E, &N, &C);

      // Convert C to int and mod 26
      int c = bignum_to_int(&C) % 26;

      //  Convert it to its orignal ascii
      ciphertext[i] = isupper(plaintext[i]) ? c + 'A' - 1 : c + 'a' - 1;
    }
    else
    {
      ciphertext[i] = plaintext[i];
    }
  }

  return ciphertext;
}

/*
 * Decrypt the ciphertext
 *
 * @param ciphertext
 * @param key
 *
 * @return plaintext
 */

char *decrypt(char ciphertext[], char key[])
{
  char *plaintext = (char *)calloc(strlen(ciphertext) + 1, sizeof(char));

  char delim[] = ",";
  char *token;

  // Get the d
  char *d_str = strtok(key, delim);
  int d = atol(d_str);

  // Get the n
  char *n_str = strtok(NULL, delim);
  int n = atol(n_str);

  // For debugging purpose
  // printf("d: %d\nn: %d\n", d, n);

  // Declare bignum variables
  // M -> plaintext
  // C -> ciphertext
  // D -> private key 1, exponent
  // N -> private key 2, modulus
  struct bn M, C, D, N;

  // Initialize bignum variables
  bignum_init(&M);
  bignum_init(&C);
  bignum_init(&D);
  bignum_init(&N);

  // Decryption
  int i;
  for (i = 0; i < strlen(ciphertext); i++)
  {
    if (isalpha(ciphertext[i]))
    {
      // Assign bignum
      bignum_from_int(&C, toupper(ciphertext[i]) - 'A' + 1);
      bignum_from_int(&D, d);
      bignum_from_int(&N, n);

      // Calculate M = (C ^ D) % N
      bignum_pow_mod(&C, &D, &N, &M);

      // Convert M to int and mod 26
      int m = bignum_to_int(&M) % 26;

      //  Convert it to its orignal ascii
      plaintext[i] = isupper(ciphertext[i]) ? m + 'A' - 1 : m + 'a' - 1;
    }
    else
    {
      plaintext[i] = ciphertext[i];
    }
  }

  return plaintext;
}

/************************************************************************************************************************
 * Helper Functions
 ************************************************************************************************************************/

/*
 * E must be less than t
 * E must be coprime with n and t
 */

int calculateE(int n, int t)
{
  int e, val;

  printf("\nList of e candidates: ");

  for (e = 2; e < t; e++)
  {
    if (e % 2 != 0 && (n % e) != 0 && (t % e) != 0)
    {
      printf("%d ", e);
    }
  }

  printf("\nChoose an e: ");
  scanf("%d", &val);
  fflush(stdin);

  return val;

  return -1;
}

/*
 * loop through the multiples of e
 * Display all candidates when m mod t is 1
 * Allow user to select a d value from the displayed d candidates
 */

int calculateD(int e, int t)
{
  int d, m, val;

  printf("\nList of d candidates: ");

  for (d = 1; d < MAX_D; d++)
  {
    if ((e * d ) % 6 == 1)
    {
      printf("%d ", d);
    }
  }

  printf("... ");

  printf("\nChoose a d: ");
  scanf("%d", &val);
  fflush(stdin);

  return val;
}

/*
 * Format text in numbers
 *
 * @param text: text in string
 * @return textNum: text in numbers
 */

int *formatTextInNum(char text[])
{
  int i;
  int *textNum = (int *)calloc(strlen(text) + 1, sizeof(int));

  for (i = 0; i < strlen(text); i++)
  {
    if (isalpha(text[i]))
    {
      textNum[i] = toupper(text[i]) - 'A' + 1;
    }
    else
    {
      textNum[i] = text[i];
    }
  }

  return textNum;
}

/************************************************************************************************************************
 * Utility Functions
 ************************************************************************************************************************/

/*
 * This function gets the text from a file.
 *
 * @param text The text to be read from the file.
 *
 * @return 1 if the text is read successfully, 0 otherwise.
 */

int getTextFromFile(char text[], char type[])
{
  char filename[MAX_SIZE];

  printf("Enter filename to open %s: ", type);
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
 * This function saves the string text to a file.
 *
 * @param text The text to be saved to the file.
 * @param type The type of the text.
 */

void saveTextToFile(char text[], char type[])
{
  char filename[MAX_SIZE];

  printf("Enter filename to save %s: ", type);
  scanf("%[^\n]", filename);
  fflush(stdin);

  FILE *file = fopen(strcat(filename, ".txt"), "w");
  if (!file)
  {
    return;
  }

  fprintf(file, "%s", text);
  fclose(file);

  printf("File saved successfully.");
}

/*
 * This function prints the text.
 *
 * @param text The text to be printed.
 */

void displayNumText(int text[])
{
  for (int i = 0; text[i] != '\0'; i++)
  {
    printf("%d ", text[i]);
  }
}

/*
 * This function displays the menu.
 */

int menu()
{
  int choice;

  printf("---------------\n");
  printf("RSA Cryptograph\n");
  printf("---------------\n");
  printf("[1] Encrypt\n");
  printf("[2] Decrypt\n");
  printf("[3] Exit\n");
  printf("\nSelect: ");

  scanf("%d", &choice);
  fflush(stdin);

  return choice;
}