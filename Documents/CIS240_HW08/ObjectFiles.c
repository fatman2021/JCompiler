
#include <stdio.h>
#include "LC4.h"


// Read an object file and modify the machine state accordingly
// Return a zero if successful and a non-zero error code if you encounter a problem
int ReadObjectFile (char *filename, MachineState *theMachineState) {
	unsigned short int *code;
	unsigned short int *addr;
	unsigned short int *n;
	unsigned short int *word;
	FILE *theFile = fopen(filename, "r");
	//check if filename was invalid
	if(theFile == NULL) {
		printf("Could not open file %s.", filename);
	}

	while(!feof(theFile)) {
		int i;
		i = fscanf(theFile, "%hx", code);
		//check that f was scanned successfully
		if(i < 1) {
			puts("Error loading file: incorrect formatting.");
			return 4;
		}
		switch(*code) {
			// could use fread for this?
			case 0xDECA :
				i = fscanf(theFile,"%hx %hx", addr, n);
				//check that f was scanned successfully
				if(i < 2) {
					puts("Error loading file: incorrect formatting.");
					return 4;
				}
				switchBytes(addr);
				switchBytes(n);
				for(i = 0; i < *n; i++) {
					if(*addr > 0x1FFF && *addr < 0x8000) {
						puts("Error loading file: attempting to write code to data address.");
						return 1;
					}
					if(fscanf(theFile, "%hx", word) < 1) {
						puts("Error loading file: incorrect formatting.");
						return 4;
					}
					switchBytes(word);
					theMachineState->memory[*addr] = *word;
					*addr = *addr + 1;
				}
				break;
			case 0xDADA :
				i = fscanf(theFile, "%hx %hx", addr, n);
				if(i < 2) {
					puts("Error loading file: incorrect formatting.");
					return 4;
				}
				switchBytes(addr);
				switchBytes(n);
				for(i = 0; i < *n; i++) {
					if(*addr < 0x2000 || *addr > 0x7FFF) {
						puts("Error loading file: attempting to write data to code address.");
						return 2;
					}
					if(fscanf(theFile, "%hx", word) < 1) {
						puts("Error loading file: incorrect formatting.");
						return 4;
					}
					switchBytes(word);
					theMachineState->memory[*addr] = *word;
					*addr = *addr + 1;
				}
				break;
			case 0xB7C3 :
				i = fscanf(theFile, "%hx %hx", addr, n);
				if(i<2) {
					puts("Error loading file: incorrect formatting.");
					return 4;
			 	}
				switchBytes(n);
				for(i = 0; i < *n; i++) {
					fscanf(theFile, "%*hhx");
				}
				break;
			case 0x7EF1 :
				i = fscanf(theFile, "%hx", n);
				if(i < 1) {
					puts("Error loading file: incorrect formatting.");
					return 4;
				}
				switchBytes(n);
				for(i = 0; i < *n; i++) {
					fscanf(theFile, "%*hhx");
				}
				break;
			case 0x5E71 :
				i = fscanf(theFile, "%hx %*hx %*hx", addr);
				if(i < 3) {
					puts("Error loading file: incorrect formatting.");
					return 4;
				}
		}
	}
	return 0;
}


void switchBytes(unsigned short int *x) {
	unsigned short int high = (*x >> 8) & 0xFF;
	*x = *x << 8;
	*x = *x + high;
}