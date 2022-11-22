#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALPHA 26
#define MAX_SIZE 255

int menu();

unsigned long long int power(unsigned long long int, unsigned long long int);
unsigned long long int calculateE(unsigned long long int, unsigned long long int);
unsigned long long int calculateD(unsigned long long int, unsigned long long int);

unsigned long long int *formatPlaintext(char[]);
unsigned long long int *formatCiphertext(char[]);

char *encrypt(char[]);
char *decrypt(char[], char[]);

int getTextFromFile(char[], char[]);
void saveTextToFile(char[], char[]);
void displayNumText(unsigned long long int[]);

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
        unsigned long long int *plaintext_num = formatPlaintext(plaintext_str);
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
        unsigned long long int *ciphertext_num = formatCiphertext(ciphertext_str);
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

unsigned long long int power(unsigned long long int num, unsigned long long int pow)
{
  unsigned long long int result = 1;
  int i;
  for (i = 0; i < pow; i++)
  {
    result *= num;
  }

  return result;
}

/*
 * Must be less than t
 * Must be coprime with n and t
 */
unsigned long long int calculateE(unsigned long long int n, unsigned long long int t)
{
  unsigned long long int e;

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
unsigned long long int calculateD(unsigned long long int e, unsigned long long int t)
{
  unsigned long long int d, m;
  for (d = 1, m = e; d < 100; m += e, d++)
  {
    if (d != e && m % t == 1)
    {
      printf("%llu ", d);
    }
  }

  unsigned long long int val;
  printf("\nChoose a d value from above: ");
  scanf("%llu", &val);
  fflush(stdin);

  return val;
}

/*
 * Convert plaintext to numbers
 *
 * @param plaintext_str Plaintext in letters
 * @return Plaintext in numbers
 */
unsigned long long int *formatPlaintext(char text[])
{
  int i, j;
  int len = strlen(text);
  unsigned long long int *num = (unsigned long long int *)calloc(len + 1, sizeof(unsigned long long int));

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
unsigned long long int *formatCiphertext(char text[])
{
  int i;
  unsigned long long int *ciphertext = (unsigned long long int *)calloc(MAX_SIZE, sizeof(unsigned long long int));

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
  unsigned long long int p;
  unsigned long long int q;

  printf("\n\nEnter two prime numbers (p and q): ");
  scanf("%llu %llu", &p, &q);
  fflush(stdin);

  // Let N = p * q
  unsigned long long int n = p * q;

  // Get the Euler Totient
  unsigned long long int t = (p - 1) * (q - 1);

  // (e * d) mod t = 1
  unsigned long long int e = calculateE(n, t);
  unsigned long long int d = calculateD(e, t);

  // printf("e: %llu\nd: %llu\nt: %llu\nn: %llu\n", e, d, t, n);

  char delim = ',';

  char private_key_str[MAX_SIZE];
  sprintf(private_key_str, "%llu%c%llu", d, delim, n);
  printf("\nPrivate Key: %s\n", private_key_str);
  saveTextToFile(private_key_str, "private key");

  char public_key_str[MAX_SIZE];
  sprintf(public_key_str, "%llu%c%llu", d, delim, n);
  printf("\n\nPublic Key: %s\n", public_key_str);
  saveTextToFile(public_key_str, "public key");

  // Encryption c = (p ^ e) % n
  int i;
  for (i = 0; i < strlen(plaintext); i++)
  {
    if (isalpha(plaintext[i]))
    {
      unsigned long long int p = toupper(plaintext[i]) - 'A' + 1;
      unsigned long long int c = power(p, e) % n;

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
  unsigned long long int d = atol(d_str);

  char *n_str = strtok(NULL, delim);
  unsigned long long int n = atol(n_str);

  // printf("d: %llu\ne: %llu\n", d, n);

  // Decryption p = (c ^ d) % n
  int i;
  for (i = 0; ciphertext[i] != '\0'; i++)
  {
    if (isalpha(ciphertext[i]))
    {
      unsigned long long int c = toupper(ciphertext[i]) - 'A' + 1;
      unsigned long long int p = power(c, d) % n;

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
void displayNumText(unsigned long long int text[])
{
  for (int i = 0; text[i] != '\0'; i++)
  {
    printf("%llu ", text[i]);
  }
}
