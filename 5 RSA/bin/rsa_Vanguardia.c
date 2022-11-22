#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALPHA 26
#define MAX_SIZE 255

int menu();

int power(int, int);
int calculateE(int, int);
int calculateD(int, int);

int *formatPlaintext(char[]);
int *formatCiphertext(char[]);

char *encrypt(char[]);
char *decrypt(char[], char[]);

int getTextFromFile(char[], char[]);
void saveTextToFile(char[], char[]);
void displayNumText(int[]);

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
        // Plaintext in letters
        printf("Plaintext: %s", plaintext_str);

        // Plaintext in numbers
        int *plaintext_num = formatPlaintext(plaintext_str);
        printf("Plaintext in numbers: ");
        displayNumText(plaintext_num);

        // Encryption Process
        char *ciphertext = encrypt(plaintext_str);
        printf("\n\nCiphertext: %s", ciphertext);

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
        // Ciphertext
        printf("Ciphertext: %s", ciphertext_str);
        int *ciphertext_num = formatCiphertext(ciphertext_str);
        printf("Ciphertext in numbers: ");
        displayNumText(ciphertext_num);
        printf("\n\n");

        char public_key_str[MAX_SIZE];
        int r2 = getTextFromFile(public_key_str, "public key");
        if (r2)
        {
          printf("Public key: %s\n", public_key_str);

          // Decryption Process
          char *plaintext = decrypt(ciphertext_str, public_key_str);
          printf("\nPlaintext: %s", plaintext);

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
 * Implement exponentiation function
 *
 * @param base
 * @param exponent
 *
 * @return base^exponent
 */

int power(int base, int exponent)
{
  int result = 1;
  int i;
  for (i = 0; i < exponent; i++)
  {
    result *= base;
  }

  return result;
}

/*
 * Must be less than t
 * Must be coprime with n and t
 */
int calculateE(int n, int t)
{
  int e;

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
 * loop through the multiples of t,
 * Display all candidates when m mod t is 1
 * Allow user to select a d value
 */
int calculateD(int e, int t)
{
  int d, m;
  for (d = 1, m = e; d < 100; m += e, d++)
  {
    if (d != e && m % t == 1)
    {
      printf("%d ", d);
    }
  }

  int val;
  printf("\nChoose a d value from above: ");
  scanf("%d", &val);
  fflush(stdin);

  return val;
}

/*
 * Convert plaintext to numbers
 *
 * @param plaintext_str Plaintext in letters
 * @return Plaintext in numbers
 */
int *formatPlaintext(char text[])
{
  int i, j;
  int len = strlen(text);
  int *num = (int *)calloc(len + 1, sizeof(int));

  for (i = 0; i < len; i++)
  {
    if (isalpha(text[i]))
    {
      num[i] = toupper(text[i]) - 'A' + 1;
    }
    else
    {
      num[i] = ' ';
    }
  }

  return num;
}

/*
 * Format ciphertext to numbers
 *
 * @param text: ciphertext in string
 * @return: ciphertext in numbers
 */
int *formatCiphertext(char text[])
{
  int i;
  int *ciphertext = (int *)calloc(MAX_SIZE, sizeof(int));

  for (i = 0; i < strlen(text); i++)
  {
    ciphertext[i] = text[i] - 'A' + 1;
  }

  return ciphertext;
}

/*
 * Encrypt the plaintext
 *
 * @param plaintext
 * @param size
 *
 * @return ciphertext
 */
char *encrypt(char plaintext[])
{
  char *ciphertext = (char *)calloc(strlen(plaintext) + 1, sizeof(char));

  // Two random prime numbers
  int p;
  int q;

  printf("\n\nEnter two prime numbers (p and q): ");
  scanf("%d %d", &p, &q);
  fflush(stdin);

  // Let N = p * q
  int n = p * q;

  // Get the Euler Totient
  int t = (p - 1) * (q - 1);

  // (e * d) mod t = 1
  int e = calculateE(n, t);
  int d = calculateD(e, t);

  // printf("e: %d\nd: %d\nt: %d\nn: %d\n", e, d, t, n);

  char delim = ',';

  char private_key_str[MAX_SIZE];
  sprintf(private_key_str, "%d%c%d", e, delim, n);
  printf("\nPrivate Key: %s\n", private_key_str);
  saveTextToFile(private_key_str, "private key");

  char public_key_str[MAX_SIZE];
  sprintf(public_key_str, "%d%c%d", d, delim, n);
  printf("\n\nPublic Key: %s\n", public_key_str);
  saveTextToFile(public_key_str, "public key");

  // Encryption c = (p ^ e) % n
  int i;
  for (i = 0; i < strlen(plaintext); i++)
  {
    if (isalpha(plaintext[i]))
    {
      int p = toupper(plaintext[i]) - 'A' + 1;
      int c = power(p, e) % n;

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
 * @param public_key_str
 *
 * @return plaintext
 */
char *decrypt(char ciphertext[], char public_key_str[])
{
  char *plaintext = (char *)calloc(MAX_SIZE, sizeof(char));

  char delim[] = ",";
  char *token;

  char *d_str = strtok(public_key_str, delim);
  int d = atol(d_str);

  char *n_str = strtok(NULL, delim);
  int n = atol(n_str);

  // printf("d: %d\ne: %d\n", d, n);

  // Decryption p = (c ^ d) % n
  int i;
  for (i = 0; ciphertext[i] != '\0'; i++)
  {
    if (isalpha(ciphertext[i]))
    {
      int c = toupper(ciphertext[i]) - 'A' + 1;
      int p = power(c, d) % n;

      plaintext[i] = isupper(ciphertext[i]) ? p + 'A' - 1 : p + 'a' - 1;
    }
    else
    {
      plaintext[i] = ciphertext[i];
    }
  }

  return plaintext;
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
