/*
 * Simple test of formatted input/output
 */

#include <stdio.h>


int main ()
{
  int a = 23, b;
  float f = 3.14159;
  char firstname[80], lastname[80];

  printf ("Here is a formatted string\n");
  printf ("Here is an example of printing an integer %5d\n", a);
  printf ("Here is an example of printing the same number in hex %5x\n", a);
  printf ("Here is an example of printing a float %8.3f\n", f);

  while (1) {
    // Print the prompt
    printf ("Please enter your name and a number : ");

    // Read the input
    a = scanf ("%s %s %d", firstname, lastname, &b);

    // Check if we successfully read all three inputs
    if (a == 3) {
      // Example of printing out strings
      printf ("Flipping your name:  %s,%s\n", lastname, firstname);
      
      printf ("%d in hex is %x\n", b, b);
      
    } else  {
      printf ("You didn't enter the values correctly\n");
    }

    // Print the output
  }

  return 0;
}
