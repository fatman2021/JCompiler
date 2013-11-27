/*
 * ObjectFiles.h
 */

#include "LC4.h"

// Read an object file and modify the machine state accordingly
// Return a zero if successful and a non-zero error code if you encounter a problem
int ReadObjectFile (char *filename, MachineState *theMachineState);
// switch upper and lower bytes of short pointed to by x
void switchBytes(unsigned short int *x);