/*
 * Reading a binary file
 */

#include <stdio.h>

int main ()
{

  int num1, i;
  FILE *theFile;

  // Open up a file for binary reading
  theFile = fopen ("output_file", "rb");

  if (theFile == NULL) {
    printf ("Couldn't open file\n");
    return 1;
  }
  
  // Read the characters from the file one at a time until
  // you hit the end of the file - EOF
  i = 0;
  do {
    num1 = fgetc (theFile);
    printf ("Byte %5d = %02x\n", i, num1);
    ++i;
  } while (num1 != EOF);

  // rewind the file
  rewind (theFile);

  printf ("\n");

  // Read the bytes in the file as integers
  // note fread returns the number of elements successfully read
  i = 0;
  while (fread(&num1, sizeof(int), 1, theFile) == 1) {
    printf ("Integer %d = %08x\n", i, num1);
    ++i;
  }

  fclose (theFile);
  return 0;
}
