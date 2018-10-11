/*!
	\file
        Main file
*/

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
int stringCmp    (const void* a, const void* b);
int stringBackCmp(const void* a, const void* b);

int printArrayOfStrings(int arrayLength, char** array, FILE* outputFile);
int countSymbolsInFile(FILE* inputFile);
/*!
 	\function
	Main function. 
	In this function I use declared functions to sort, backsort and write out "Hamlet" poem from file;
*/
int main()
{
  FILE* inputFile  = fopen(INPUT,  "r");
  assert(inputFile != nullptr);
  char* originalPoem = NULL;
  char** originalLinkedPoem = NULL;
  char** sortedLinkedPoem = NULL;
  char** backSortedLinkedPoem = NULL;	
  int strLength = 0;
  int arrayLength = 0;
  int i = 0;
  originalPoem = fileToString(inputFile, &strLength);
  
  originalLinkedPoem = stringToPtr(originalPoem, strLength, &arrayLength); 
  sortedLinkedPoem =  ptrArrayCopy(originalLinkedPoem, arrayLength);
  backSortedLinkedPoem = ptrArrayCopy(originalLinkedPoem, arrayLength);
   
  qsort(sortedLinkedPoem, arrayLength, sizeof(char*), stringCmp);	
  qsort(backSortedLinkedPoem, arrayLength, sizeof(char*), stringBackCmp); 
  
  fclose(inputFile);
  FILE* outputFile = fopen(OUTPUT, "w");
 
  printArrayOfStrings(arrayLength, sortedLinkedPoem,     outputFile);
  printArrayOfStrings(arrayLength, backSortedLinkedPoem, outputFile);
  printArrayOfStrings(arrayLength, originalLinkedPoem,   outputFile);
  
	
  fclose(outputFile);
  free(backSortedLinkedPoem);
  free(sortedLinkedPoem);
  free(originalLinkedPoem);
    
}

/*!
	\function
	Function that reads text from file(must be opened in read mode) and puts it to the string
 	\param file
	Pointer to the file with poem
	\param stringLength
	Pointer to the variable where length of the final string will be stored;
	\return returns string made from file
*/
char* fileToString(FILE* file, int* stringLength)
{
  assert(file != NULL);
  assert(stringLength != NULL);
	
  *stringLength = countSymbolsInFile(file);	
  char* string = (char*)calloc(*stringLength, sizeof(char));
  fread(string, *stringLength, 1, file);
 
  return string;
}
/*!
	\function This function translates string with "\n" symbols to pointer array (can be used to translate text to the stribg array where every line is a different string)
	\param string String that should be translated
	\param stringLength length of the string that should be translated
	\param arrayLength pointer to the variable where array length should be stored(can be null);
	\return returns array of strings.
*/

char** stringToPtr(char* string, int stringLength, int* arrayLength)
{
  assert(string!=NULL);
  assert(stringLength >= 0);
  assert(arrayLength!=NULL);

  int i = 0;
  int iterator = 0;
  char** ptrArray = {};
  
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
/*!
	\function Copyes pointer array
	\param ptrArray pointer array that should be copied;
	\param arrayLength length of the array
	\return returns pointer to the new array with values from old one
*/
char** ptrArrayCopy(char** ptrArray, int arrayLength)
{
  assert(ptrArray != NULL);
  assert(arrayLength >= 0);
  
  char** returned = (char**)calloc(arrayLength, sizeof(char*));
  int i = 0;
  for(i = 0; i < arrayLength; i++)
  {
    returned[i] = ptrArray[i];
  }
  return returned;
}
/*!
	\function Comparator for qsort
*/
int stringCmp(const void* a, const void* b)
{
  assert(a != NULL);
  assert(b != NULL);  

  const char* pa = *(const char**)a;
  const char* pb = *(const char**)b;
  return strcasecmp(pa, pb);
}

int stringBackCmp(const void* a, const void* b)
{
  assert(a != NULL);
  assert(b != NULL);  

  const char* pa = *(const char**)a;
  const char* pb = *(const char**)b;
  aLen = strlen(pa);
  bLen = strlen(pb);
  
  while((pa[aLen] == pb[bLen] || ispunct(pa[aLen]) || ispunct(pb[bLen])) && aLen >= 0 && bLen >= 0)
  {
    if(ispunct(pa[aLen]) || pa[aLen] == ' ')
      aLen--;
    else if(ispunct(pb[bLen]) || pb[bLen] == ' ')
      bLen--;
    else 
    {
      aLen--;
      bLen--;
    }
  }
  return(aLen - bLen);
}

/*!
	\function Reverses string;
	\param str String that should be reversed
	\return returns reversed string
*/
char* stringReverse(char* str)
{
    assert(str != NULL);

    int right = strlen(str) - 1, left = 0;

    char ch = '\n';
    while (right > left)
    {
        ch = str[right];
        str[right] = str[left];
        str[left] = ch;
        right--;
        left++;
    }
    return str;
}

int printArrayOfStrings(int arrayLength, char** array, FILE* outputFile)
{
  assert(array != NULL);
  assert(arrayLength >= 0);
  int i = 0;
  for(i = 0; i < arrayLength; i++)
    if(array[i][0] != '\0') 
      fprintf(outputFile, "%s\n", array[i]);
}

int countSymbolsInFile(FILE* inputFile)
{
  assert(FILE* != NULL);
  
  fseek(inputFile, 0L, SEEK_END);
  int length = ftell(file);
  fseek(inputFile, 0L, SEEK_SET);
  return length;
}
