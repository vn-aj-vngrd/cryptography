#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_SIZE 256

int getRandomShift();
char *generateOTP(char text[]);

char *reverse(char text[]);
char *shift(char text[], char key[]);
char *vernam(char text[], char key[]);

int menu();
int getTextFromFile(char text[]);
void saveTextToFile(char text[]);

#endif