#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 9999
#define MAX_ROUND 10

char *encrypt(char text[]);
char *decrypt(char text[], char key[]);

void atbash(char text[]);
void shift(char text[], char shift_key[]);
void vigenere(char text[], char vigenere_key[], int type);
void vernam(char text[], char otp[]);
void transposition(char text[], char transposition_key[], int type);
void reverseKey(char key[]);

char *generateKey(int size);
char *inverseShiftKey(char key[]);
char *generateTranspositionKey(int size);

int menu();
int getTextFromFile(char text[], char type[]);
void saveTextToFile(char text[], char type[]);

#endif