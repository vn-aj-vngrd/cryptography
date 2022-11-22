#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Libraries
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper Libary to store and manipulate large numbers
#include "lib/bn.c"

// Macros
#define MAX_ALPHA 26
#define MAX_SIZE 256
#define MAX_D 300

// Function Prototypes
char *rsa_encrypt(char plaintext[]);
char *rsa_decrypt(char ciphertext[], char public_key_str[]);

int calculateE(int n, int t);
int calculateD(int e, int t);

int *formatPlaintext(char text[]);
int *formatCiphertext(char text[]);

int getTextFromFile(char text[], char type[]);
void saveTextToFile(char text[], char type[]);
void displayNumText(int text[]);
int menu();

#endif