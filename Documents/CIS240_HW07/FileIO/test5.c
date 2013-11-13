/*
 * Writing a binary file
 */

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 4

int main ()
{
  int num1 = 0xFEDC;
  int num2 = 0x1234;
  int num3 = 0xF1E2D3C4;
  int num4 = 0x01020304;

  int array[ARRAY_SIZE], i;

  FILE *theFile;

  // Initialize array with random integral values
  for (i=0; i < ARRAY_SIZE; ++i)
    array[i] = rand();


  // Open up a file for binary writing
  theFile = fopen ("output_file", "wb");

  if (theFile == NULL) {
    printf ("Couldn't open file\n");
    return 1;
  }
  
  // Write the numbers
  fwrite (&num1, sizeof(int), 1, theFile);
  fwrite (&num2, sizeof(int), 1, theFile);
  fwrite (&num3, sizeof(int), 1, theFile);
  fwrite (&num4, sizeof(int), 1, theFile);

  // Write the array
  fwrite (array, sizeof(int), ARRAY_SIZE, theFile);  

  fclose (theFile);
  return 0;
}
