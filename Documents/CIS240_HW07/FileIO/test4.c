/*
 * Reading a formatted text file
 */

#include <stdio.h>

#define MAX_LINE_LENGTH 80

int main ()
{
  int i, num1, num2;
  char input[MAX_LINE_LENGTH];
  char fname[MAX_LINE_LENGTH];
  FILE *theFile;

  // Open up a file for reading
  theFile = fopen ("script_file.txt", "r");

  if (theFile == NULL) {
    printf ("Couldn't open file\n");
    return 1;
  }

  // Loop around reading lines of input from the file
  // note that fgets returns NULL when it encounters the end of the file EOF
  while (fgets (input, MAX_LINE_LENGTH, theFile)) {
    printf ("\nI just read this string  : %s\n", input);

    // Here we use sscanf to attempt to parse the string that we just read

    // See if it's a load command
    if (sscanf (input, "load %s", fname) == 1) {
      printf ("It's a load command - fname = %s\n", fname);
    }

    // See if it's a set command
    if (sscanf (input, "set R%d %x", &num1, &num2) == 2) {
      printf ("It's a set command : Set register %d to %x\n", num1, num2);
    } 

    // See if it's a script command
    if (sscanf (input, "script %s", fname) == 1) {
      printf ("It's a script command - fname = %s\n", fname);
    }

    // See if it's a break command
    if (sscanf (input, "break %x", &num1) == 1) {
      printf ("It's a break command : break at PC = %d\n", num1);
    } 

    printf ("##############################\n");
  }

  fclose (theFile);
  return 0;
}
