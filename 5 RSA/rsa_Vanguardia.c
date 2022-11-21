#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALPHA 26
#define MAX_SIZE 255

int menu();
long int calculateE(long int, long int);
long int calculateD(long int, long int);
long int encrypt(long int);
long int decrypt(long int, char[]);
int getTextFromFile(char[], char[]);
void saveTextToFile(char[], char[]);

int main()
{
  do
  {
    int choice = menu();

    if (choice == 1)
    {
      char plaintext_str[MAX_SIZE];
      int r = getTextFromFile(plaintext_str, "plaintext");

      if (r)
      {
        long int plaintext = atol(plaintext_str);
        printf("Plaintext: %ld\n", plaintext);

        long int ciphertext = encrypt(plaintext);
        printf("\n\nCiphertext: %ld\n", ciphertext);

        char ciphertext_str[MAX_SIZE];
        sprintf(ciphertext_str, "%ld", ciphertext);
        saveTextToFile(ciphertext_str, "ciphertext");
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
        long int ciphertext = atol(ciphertext_str);
        printf("Ciphertext: %ld\n\n", ciphertext);

        char public_key_str[MAX_SIZE];
        int r2 = getTextFromFile(public_key_str, "public key");
        if (r2)
        {
          printf("Public key: %s\n", public_key_str);

          long int plaintext = decrypt(ciphertext, public_key_str);
          printf("\nPlaintext: %ld\n", plaintext);

          char plaintext_str[MAX_SIZE];
          sprintf(plaintext_str, "%ld", plaintext);
          saveTextToFile(plaintext_str, "plaintext");
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
/*
 * Must be less than t
 * Must be coprime with n and t
 */
long int calculateE(long int n, long int t)
{
  long int e;

  for (e = 2; e < t; e++)
  {
    if (e % 2 != 0 && (n % e) != 0 && (t % e) != 0)
    {
      return e;
    }
  }

  return -1;
}

/*
 * Choose e x d mod t = 1
 */
long int calculateD(long int e, long int t)
{
  // loop through the multiples of t and return when mod t is 1
  long int d, m;
  for (d = 1, m = e; 1; m += e, d++)
  {
    if (m % t == 1)
    {
      return d;
    }
  }
}

/*
 * Encrypt the plaintext
 *
 * @param plaintext
 *
 * @return ciphertext
 */
long int encrypt(long int plaintext)
{
  // Two random prime numbers
  long int p;
  long int q;

  printf("\nEnter two prime numbers (p and q): ");
  scanf("%ld %ld", &p, &q);
  fflush(stdin);

  // Let N = p * q
  long int n = p * q;

  // Get the Euler Totient
  long int t = (p - 1) * (q - 1);

  // (e * d) mod t = 1
  long int e = calculateE(n, t);
  long int d = calculateD(e, t);

  // printf("e: %ld\nd: %ld\nt: %ld\nn: %ld\n", e, d, t, n);

  printf("\nPrivate Key: %ld,%ld\n", e, n);

  char delim = ',';
  char public_key_str[MAX_SIZE];
  // concat d + delim + n
  sprintf(public_key_str, "%ld%c%ld", d, delim, n);
  printf("Public Key: %s\n", public_key_str);
  saveTextToFile(public_key_str, "public key");

  // Encryption c = (msg ^ e) % n
  long int c = (int)pow(plaintext, e);
  c = fmod(c, n);

  return c;
}

/*
 * Decrypt the ciphertext
 *
 * @param ciphertext
 * @param public_key_str
 *
 * @return plaintext
 */
long int decrypt(long int ciphertext, char public_key_str[])
{
  char delim[] = ",";
  char *token;

  char *d_str = strtok(public_key_str, delim);
  char *n_str = strtok(NULL, delim);

  // e_str to long int
  long int d = atol(d_str);

  // d_str to long int
  long int n = atol(n_str);

  // printf("d: %ld\ne: %ld\n", e, d);

  // Decryption m = (c ^ d) % n
  long int m = pow(ciphertext, d);
  m = fmod(m, n);

  return m;
}

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
 * This function saves the text to a file.
 *
 * @param text The text to be saved to the file.
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