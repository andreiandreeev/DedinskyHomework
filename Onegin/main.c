#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define INPUT "text"
#define OUTPUT "sorted"

char* fileToString(FILE* file, int* stringLength);
char** stringToPtr(char* string, int stringLength, int* arrayLength);
char** ptrArrayCopy(char** ptrArray, int arrayLength);
char* stringReverse(char* str);
int stringCmp(const void* a, const void* b);

int main()
{
  FILE* inputFile  = fopen(INPUT,  "r");
  char* originalPoem;
  char** originalLinkedPoem;
  char** sortedLinkedPoem;
  char** backSortedLinkedPoem;
  int strLength;
  int arrayLength = 0;
  int i;
  originalPoem = fileToString(inputFile, &strLength);
  
  originalLinkedPoem = stringToPtr(originalPoem, strLength, &arrayLength); 
  sortedLinkedPoem =  ptrArrayCopy(originalLinkedPoem, arrayLength);
  backSortedLinkedPoem = ptrArrayCopy(originalLinkedPoem, arrayLength);
   
  qsort(sortedLinkedPoem, arrayLength, sizeof(char*), stringCmp);

  for(i = 0; i < arrayLength; i++)
    backSortedLinkedPoem[i] = stringReverse(backSortedLinkedPoem[i]);
  
  qsort(backSortedLinkedPoem, arrayLength, sizeof(char*), stringCmp); 
  
  for(i = 0; i < arrayLength; i++)
    backSortedLinkedPoem[i] = stringReverse(backSortedLinkedPoem[i]);

 
  fclose(inputFile);
  FILE* outputFile = fopen(OUTPUT, "w");

  for(i = 0; i < arrayLength; i++)
    if(sortedLinkedPoem[i][0] != '\0') 
      fprintf(outputFile, "%s\n", sortedLinkedPoem[i]);
  for(i = 0; i < arrayLength; i++)
    if(sortedLinkedPoem[i][0] != '\0')
      fprintf(outputFile, "%s\n", backSortedLinkedPoem[i]);
  for(i = 0; i < arrayLength; i++)
    if(originalLinkedPoem[i][0] != '\0')
      fprintf(outputFile, "%s\n", originalLinkedPoem[i]);

  fclose(outputFile);
  free(backSortedLinkedPoem);
  free(sortedLinkedPoem);
  free(originalLinkedPoem);
    
}

char* fileToString(FILE* file, int* stringLength)
{
  assert(file != NULL);
  assert(stringLength != NULL);

  fseek(file, 0L, SEEK_END);
  *stringLength = ftell(file);
  fseek(file, 0L, SEEK_SET);
  char* string = (char*)calloc(*stringLength, sizeof(char));
  fread(string, *stringLength, 1, file); 
  return string;
}

char** stringToPtr(char* string, int stringLength, int* arrayLength)
{
  int i = 0;
  int iterator = 0;
  char** ptrArray;
  
  for(i = 0; i < stringLength; i++)
    if(string[i] == '\n' || string[i] == '\0')
      iterator++;
  *arrayLength = iterator;
  ptrArray = (char**)calloc(*arrayLength, sizeof(char*));
  
  iterator = 0;
  ptrArray[0] = string;
  for(i = 0; i < stringLength; i++)
  {
    if(string[i] == '\n')
    {
      ptrArray[iterator++] = &string[i+1];
      string[i] = '\0'; 
    }
  }
  return ptrArray; 
}

char** ptrArrayCopy(char** ptrArray, int arrayLength)
{
  char** returned = (char**)calloc(arrayLength, sizeof(char*));
  int i;
  for(i = 0; i < arrayLength; i++)
  {
    returned[i] = ptrArray[i];
  }
  return returned;
}

int stringCmp(const void* a, const void* b)
{
  const char* pa = *(const char**)a;
  const char* pb = *(const char**)b;
  return strcasecmp(pa, pb);
}

char* stringReverse(char *str)
{
    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}
