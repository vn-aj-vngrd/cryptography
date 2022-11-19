#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_SIZE 256
#define MAX_ROUNDS 10

char *encrypt(char text[]);
char *decrypt(char text[], char key[]);

void atbash(char text[]);
void shift(char text[], char shift_key[]);
void vigenere(char text[], char vigenere_key[], int type);
void vernam(char text[], char otp[]);
void reverseText(char text[]);

char *generateKey(int size);
char *decryptShiftKey(char key[]);

int menu();
int getTextFromFile(char text[], char type[]);
void saveTextToFile(char text[], char type[]);

#endif