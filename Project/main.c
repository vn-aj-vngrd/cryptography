#include <stdio.h>

#include "functions.c"

int main()
{
  do
  {
    char text[MAX_SIZE];

    int choice = menu();

    if (choice == 1)
    {
      int res = getTextFromFile(text);
      if (res)
      {
      }
      else
      {
        printf("Error: Failed to read the file.");
      }
    }
    else if (choice == 2)
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
