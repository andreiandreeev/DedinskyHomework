
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT "text"
#define OUTPUT "sorted"
char* fileToString(FILE* file, int* stringLength);
char** stringToPtrArray(char* string, int stringLength, int* arrayLength);
int stringCmp(char* a, char* b);

int main()
{
  FILE* file = fopen(INPUT, "r");
  char* stringFromFile;
  char** ptrArray;
  int stringLength;
  int arrayLength;

  stringFromFile = fileToString(file, &stringLength);
  ptrArray = stringToPtrArray(stringFromFile, stringLength, &arrayLength);
 
  fclose(file);
  file = fopen(OUTPUT, "w"); 
 /* qsort(ptrArray, arrayLength, sizeof(char*), stringCmp);
  */
  int i;
  for(i = 0; i < arrayLength; i++)
  {
    fprintf(file, "%s\n", ptrArray[i]);
  }
  
  free(stringFromFile);
  free(ptrArray);
  
  fclose(file);
  return 0;
}

char* fileToString(FILE* file, int* stringLength)
{
  fseek(file, 0L, SEEK_END);
  *stringLength = ftell(file) + 1;
  fseek(file, 0L, SEEK_SET);
  printf("%d", *stringLength);
  char* string = (char*)calloc(*stringLength, sizeof(char));
  fread(string, *stringLength, 1, file);
  
  return string;
}

char** stringToPtrArray(char* string, int stringLength, int* arrayLength)
{
  int i;
  char** ptrArray;
  *arrayLength = 0;
  
  for(i = 0; i < stringLength; i++)
    if(string[i] == '\n' || string[i] == '\0')
      *arrayLength++;
  
  ptrArray = (char**)calloc(*arrayLength, sizeof(char*));
  
  int iterator = 0;
  
  for(i = 0; i < stringLength; i++)
  {
    if(string[i] == '\n' || string[i] == '\0')
    {
      string[i] = '\0';
      ptrArray[iterator++] = &string[i];
    }
  }
  return ptrArray;
}
