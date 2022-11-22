#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALPHA 26
#define MAX_SIZE 255

int menu();

long long int power(long long int, long long int);
long long int calculateE(long long int, long long int);
long long int calculateD(long long int, long long int);
long long int *formatPlaintext(char[]);
long long int *formatCiphertext(char[]);
char *formalOriginalText(long long int[]);

long long int *encrypt(long long int[], int);
long long int *decrypt(long long int[], char[]);

int getTextFromFile(char[], char[]);
void saveStringToFile(char[], char[]);
void saveNumToFile(long long int[], char[]);
void displayNumText(long long int[]);

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
        printf("Plaintext: %s\n", plaintext_str);

        // Plaintext in numbers
        long long int *plaintext_num = formatPlaintext(plaintext_str);
        printf("Plaintext in numbers: ");
        displayNumText(plaintext_num);

        // Encryption Process
        long long int *ciphertext_num = encrypt(plaintext_num, strlen(plaintext_str));
        printf("\n\nCiphertext: ");
        displayNumText(ciphertext_num);
        printf("\n");

        // Save ciphertext to file
        saveNumToFile(ciphertext_num, "ciphertext");
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
        printf("Ciphertext: %s\n\n", ciphertext_str);
        long long int *ciphertext_num = formatCiphertext(ciphertext_str);

        char public_key_str[MAX_SIZE];
        int r2 = getTextFromFile(public_key_str, "public key");
        if (r2)
        {
          printf("Public key: %s\n", public_key_str);

          // Decryption Process
          long long int *plaintext = decrypt(ciphertext_num, public_key_str);
          printf("\nPlaintext: ");
          displayNumText(plaintext);

          // Convert plaintext to letters
          char *orignal_message = formalOriginalText(plaintext);
          printf("\nOriginal message: %s\n", orignal_message);

          // Save plaintext to file
          saveStringToFile(orignal_message, "plaintext");
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

long long int power(long long int num, long long int pow)
{
  long long int result = 1;
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
long long int calculateE(long long int n, long long int t)
{
  long long int e;

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
long long int calculateD(long long int e, long long int t)
{
  // loop through the multiples of t and return when mod t is 1
  long long int d, m;
  for (d = 1, m = e; d < 100; m += e, d++)
  {
    if (d != e && m % t == 1)
    {
      printf("%lld ", d);
    }
  }

  long long int val;
  printf("\nChoose a d value from above: ");
  scanf("%lld", &val);
  fflush(stdin);

  return val;
}

long long int *formatPlaintext(char text[])
{
  int i, j;
  int len = strlen(text);
  long long int *num = (long long int *)calloc(len + 1, sizeof(long long int));

  for (i = 0; i < len; i++)
  {
    if (isalpha(text[i]))
    {
      num[i] = toupper(text[i]) - 'A' + 1;
    }
    else
    {
      num[i] = -1;
    }
  }

  return num;
}

long long int *formatCiphertext(char text[])
{
  int i;
  long long int *ciphertext = (long long int *)calloc(MAX_SIZE, sizeof(long long int));
  char delim[] = " ";

  char *token = strtok(text, delim);
  for (i = 0; token != NULL; i++)
  {
    ciphertext[i] = atoi(token);
    token = strtok(NULL, delim);
  }

  return ciphertext;
}

char *formalOriginalText(long long int text[])
{
  int i;
  char *original_text = (char *)calloc(MAX_SIZE, sizeof(char));

  for (i = 0; text[i] != '\0'; i++)
  {
    original_text[i] = text[i] + 'A' - 1;
  }

  original_text = (char *)realloc(original_text, (i + 1) * sizeof(char));

  return original_text;
}

/*
 * Encrypt the plaintext
 *
 * @param plaintext
 * @param size
 *
 * @return ciphertext
 */
long long int *encrypt(long long int plaintext[], int len)
{
  long long int *ciphertext = (long long int *)calloc(len + 1, sizeof(long long int));

  // Two random prime numbers
  long long int p;
  long long int q;

  printf("\n\nEnter two prime numbers (p and q): ");
  scanf("%lld %lld", &p, &q);
  fflush(stdin);

  // Let N = p * q
  long long int n = p * q;

  // Get the Euler Totient
  long long int t = (p - 1) * (q - 1);

  // (e * d) mod t = 1
  long long int e = calculateE(n, t);
  long long int d = calculateD(e, t);

  // printf("e: %lld\nd: %lld\nt: %lld\nn: %lld\n", e, d, t, n);

  printf("\nPrivate Key: %lld,%lld\n", e, n);

  char delim = ',';
  char public_key_str[MAX_SIZE];
  // concat d + delim + n
  sprintf(public_key_str, "%lld%c%lld", d, delim, n);
  printf("Public Key: %s\n", public_key_str);
  saveStringToFile(public_key_str, "public key");

  // Encryption c = (p[i] ^ e) % n
  int i;
  for (i = 0; i < len; i++)
  {
    ciphertext[i] = power(plaintext[i], e) % n;
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
long long int *decrypt(long long int ciphertext[], char public_key_str[])
{
  long long int *plaintext = (long long int *)calloc(MAX_SIZE, sizeof(long long int));

  char delim[] = ",";
  char *token;

  char *d_str = strtok(public_key_str, delim);
  long long int d = atol(d_str);

  char *n_str = strtok(NULL, delim);
  long long int n = atol(n_str);

  // // printf("d: %lld\ne: %lld\n", e, d);

  // Decryption p = (c[i] ^ d) % n
  int i;
  for (i = 0; ciphertext[i] != '\0'; i++)
  {
    plaintext[i] = power(ciphertext[i], d) % n;
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
void saveStringToFile(char text[], char type[])
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
 * This function saves the num text to a file.
 *
 * @param text The text to be saved to the file.
 * @param type The type of the text.
 */
void saveNumToFile(long long int text[], char type[])
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

  int i;
  for (i = 0; text[i] != '\0'; i++)
  {
    if (text[i + 1] == '\0')
    {
      fprintf(file, "%lld", text[i]);
    }
    else
    {
      fprintf(file, "%lld ", text[i]);
    }
  }

  fclose(file);

  printf("File saved successfully.");
}

/*
 * This function prints the text.
 *
 * @param text The text to be printed.
 */
void displayNumText(long long int text[])
{
  for (int i = 0; text[i] != '\0'; i++)
  {
    printf("%lld ", text[i]);
  }
}