#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALPHA 26
#define MAX_SIZE 255

int menu();
char *encrypt(char[], char[]);
int getRandomPrimeNumber();
int getGCD(int, int);
char *decrypt(char[], char[]);
int getTextFromFile(char[]);
void saveTextToFile(char[]);

int main() {
  do {
    char text[MAX_SIZE] = "ab";
    char key[MAX_SIZE] = "ab";

    // int choice = menu();
    int choice = 1;
    if (choice == 1) {
      char *encrypted_text = encrypt(text, key);
    //   printf("Encrypted Text: %s\n", encrypted_text);

    } else if (choice == 2) {
    } else if (choice == 3) {
      printf("Thank you for using this program.");
      break;
    } else {
      printf("Invalid choice!");
    }

    printf("\n\n");

    break;
  } while (1);

  return 0;
}

int menu() {
  int choice;

  printf("Polyalphabetic Cryptograph\n");
  printf("-------------------------\n");
  printf("[1] Encrypt\n");
  printf("[2] Decrypt\n");
  printf("[3] Exit\n");
  printf("\nSelect: ");

  scanf("%d", &choice);
  fflush(stdin);

  return choice;
}

int getRandomPrimeNumber() {
  int prime_numbers[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                         43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
  int random_index = rand() % 25;
  return prime_numbers[random_index];
}

int getGCD(int a, int h) {
  int temp;
  while (1) {
    temp = a % h;
    if (temp == 0) return h;
    a = h;
    h = temp;
  }
}

char *encrypt(char plain_text[], char key[]) {
  // Create an allocated space for the encrypted text to be returned.
  char *encrypted_text = (char *)calloc(strlen(plain_text) + 1, sizeof(char));

  // Two random prime numbers
  double p = 3;
  double q = 7;
  double n = p * q;

  // Finding other part of public key.
  // e stands for encrypt
  double e = 2;
  double phi = (p - 1) * (q - 1);
  while (e < phi) {
    // e must be co-prime to phi and
    // smaller than phi.
    if (getGCD(e, phi) == 1)
      break;
    else
      e++;
  }

  // Private key (d stands for decrypt)
  // choosing d such that it satisfies
  // d*e = 1 + k * totient
  int k = 2;  // A constant value
  double d = (1 + (k * phi)) / e;

  // Message to be encrypted
  double msg = 12;

  printf("Message data = %lf", msg);

  // Encryption c = (msg ^ e) % n
  double c = pow(msg, e);
  c = fmod(c, n);
  printf("\nEncrypted data = %lf", c);

  // Decryption m = (c ^ d) % n
  double m = pow(c, d);
  m = fmod(m, n);
  printf("\nOriginal Message Sent = %lf", m);

  return encrypted_text;
}

char *decrypt(char cipher_text[], char key[]) {
  // Create an allocated space for the decrypted text to be returned.
  char *decrypted_text = (char *)calloc(strlen(cipher_text) + 1, sizeof(char));

  return decrypted_text;
}

/*
 * This function gets the text from a file.
 *
 * @param text The text to be read from the file.
 *
 * @return 1 if the text is read successfully, 0 otherwise.
 */

int getTextFromFile(char text[]) {
  char filename[MAX_SIZE];

  printf("Enter filename to open: ");
  scanf("%[^\n]", filename);
  fflush(stdin);

  FILE *file = fopen(strcat(filename, ".txt"), "r");
  if (!file) {
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

void saveTextToFile(char text[]) {
  char filename[MAX_SIZE];

  printf("Enter filename to save: ");
  scanf("%[^\n]", &filename);
  fflush(stdin);

  FILE *file = fopen(strcat(filename, ".txt"), "w");
  if (!file) {
    printf("Failed to save file.");
  }

  fprintf(file, "%s", text);
  fclose(file);

  printf("File saved successfully.");
}