#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 255

char *numToAlpha(char[]);
int getTextFromFile(char[]);
void saveTextToFile(char[]);

int main()
{
    char text[MAX_SIZE];
    int res = getTextFromFile(text);
    if (res)
    {
        printf("Text: %s\n", text);
        char *result = numToAlpha(text);
        printf("Result: %s\n", result);

        saveTextToFile(result);
    }

    return 0;
}

char *numToAlpha(char text[])
{
    char *alpha = (char *)calloc(strlen(text) + 1, sizeof(char));

    int num = 0;

    int i, j = 0;
    for (i = 0; i < strlen(text); i++)
    {

        if (text[i] == ',')
        {
            alpha[j++] = ((num % 26) + 'A') - 1;
            num = 0;
        }
        else
        {
            num = num * 10 + (text[i] - '0');
        }
    }

    return alpha;
}

int getTextFromFile(char text[])
{
    char filename[MAX_SIZE];

    printf("Enter filename to open: ");
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

void saveTextToFile(char text[])
{
    char filename[MAX_SIZE];

    printf("Enter filename to save: ");
    scanf("%[^\n]", &filename);
    fflush(stdin);

    FILE *file = fopen(strcat(filename, ".txt"), "w");
    if (!file)
    {
        printf("Failed to save file.");
    }

    fprintf(file, "%s", text);
    fclose(file);

    printf("File saved successfully.");
}