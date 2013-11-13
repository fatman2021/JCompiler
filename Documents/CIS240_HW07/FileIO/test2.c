/*
 * Outputting formatted text to a file
 */

#include <stdio.h>
#include <stdlib.h>

int main ()
{
  int i, r;
  FILE *theFile;

  // Open up a file for writing
  theFile = fopen ("text_file.txt", "w");

  for (i = 0; i < 10; ++i) {
    r = rand();
    fprintf (theFile, "Random number %d = %d\n", i, r);
  }


  // Close the file
  fclose (theFile);

  return 0;
}
