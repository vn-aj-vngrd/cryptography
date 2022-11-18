#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_SIZE 256

char *encrypt(char text[]);
char *decrypt(char text[], char key[]);

char *generateKey(int size);
char *decryptShiftKey(char key[]);

void atbash(char text[]);
void shift(char text[], char shift_key[]);
void vernam(char text[], char otp[]);

int menu();
int getTextFromFile(char text[], char type[]);
void saveTextToFile(char text[], char type[]);

#endif