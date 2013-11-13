/*
 * Reading formatted text file
 */

#include <stdio.h>

int main ()
{
  int i, num1, num2;
  FILE *theFile;

  // Open up a file for reading
  theFile = fopen ("text_file.txt", "r");

  for (i = 0; i < 10; ++i) {
    // Read a line from the file
    fscanf (theFile, "Random number %d = %d\n", &num1, &num2);

    // Print out the numbers that were read
    printf ("Just read num1 = %d and num2 = %d\n", num1, num2);
  }


  // Close the file
  fclose (theFile);
  // Close the file

  return 0;
}
