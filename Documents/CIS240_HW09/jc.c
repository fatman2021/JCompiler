#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *fileName;
int ind = 0;		
int comp_index = 0;

// checks if null-terminated string is made up of all alpha-numeric characters
// returns 1 if it is and 0 if not
int isAlnumString(char *str) {
	if(*str == 0) {
		return 0;
	}
	while(*str) {
		if(!isalnum(*str)) {
			return 0;
		}
		str++;
	}
	return 1;
}
// checks if null-terminated string is a decimal number
// returns 1 if it is and 0 if not
int isDecimalString(char *str) {
	if(*str == 0) {
		return 0;
	}
	if(*str == '-') {
		str++;
	}
	while(*str) {
		if(!isdigit(*str)) {
			return 0;
		}
		str++;
	}
	return 1;
}
// checks if null-terminated string is hex number
// returns 1 if it is and 0 if not
int isHexString(char *str) {
	if(*str == 0) {
		return 0;
	}
	if(*str != '0') {
		return 0;
	}
	str++;
	if(*str != 'x') {
		return 0;
	}
	str++;
	while(*str) {
		if(!isxdigit(*str)) {
			return 0;
		}
		str++;
	}
	return 1;

}
// reads in tokens from file. comments are not considered tokens, and are disregarded
void readToken(FILE *inStream, char *token) {
	char c = fgetc(inStream);
	// skip over all the whitespace and comments before token
	while(c!=EOF && isspace(c)) {
		c = fgetc(inStream);
	}
	if(c == ';') {
		while(c != EOF && c != '\n' ) {
			c = fgetc(inStream);
		}
	}
	while(c!=EOF && isspace(c)) {
		c = fgetc(inStream);
	}
	// build token
	while(c!=EOF && !isspace(c)) {
		// disregard everything after comment
		if(c == ';') {
			while(c != EOF && c != '\n' ) {
				c = fgetc(inStream);
			}
			break;
		}
		else {
			*token = c;
			token++;
			c = fgetc(inStream);
		}
	}
	// make token null-terminating
	*token = 0; //check this
}
void handleToken(FILE *inStream, FILE *outStream, char *token) {
	int n;
	char name[200];
	int starting_index;
	int hasElse = 0;
	int endif = 0;
	if(strcmp(token, "+") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// get values off top of stack
		fputs("\tLDR R1 R6 #1\n", outStream);
		fputs("\tADD R0 R0 R1\n", outStream);	// add and store in R0
		fputs("\tADD R6 R6 #1\n", outStream);	// update SP
		fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value onto top of stack
	}
	else if(strcmp(token, "-") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// get values off top of stack
		fputs("\tLDR R1 R6 #1\n", outStream);
		fputs("\tSUB R0 R0 R1\n", outStream);	// subtract and store in R0
		fputs("\tADD R6 R6 #1\n", outStream);	// update SP
		fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value onto top of stack
	}
	else if(strcmp(token, "*") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// get values off top of stack
		fputs("\tLDR R1 R6 #1\n", outStream);
		fputs("\tMUL R0 R0 R1\n", outStream);	// multiply and store in R0
		fputs("\tADD R6 R6 #1\n", outStream);	// update SP
		fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value onto top of stack
	}
	else if(strcmp(token, "/") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// get values off top of stack
		fputs("\tLDR R1 R6 #1\n", outStream);
		fputs("\tDIV R0 R0 R1\n", outStream);	// divide and store in R0
		fputs("\tADD R6 R6 #1\n", outStream);	// update SP
		fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value onto top of stack
	}
	else if(strcmp(token, "%") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// get values off top of stack
		fputs("\tLDR R1 R6 #1\n", outStream);
		fputs("\tMOD R0 R0 R1\n", outStream);	// mod and store in R0
		fputs("\tADD R6 R6 #1\n", outStream);	// update SP
		fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value onto top of stack
	}
	else if(strcmp(token, "lt") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// get a
		fputs("\tLDR R1 R6 #1\n", outStream); 	// get b
		fputs("\tADD R6 R6 #1\n", outStream); 	// update SP
		fputs("\tCMP R0 R1\n", outStream); 	// a - b
		fprintf(outStream, "\tBRn %s_comp_%d\n", fileName, comp_index);		// if negative, skip next 2 lines
		fputs("\tCONST R0 #0\n", outStream);	// false, so want to return 0
		fprintf(outStream, "\tBRnzp %s_comp_%d\n", fileName, comp_index + 1);		// skip next line
		fprintf(outStream, "%s_comp_%d", fileName, comp_index);
		fputs("\tCONST R0 #1\n", outStream);	// true, so want to return 1
		fprintf(outStream, "%s_comp_%d\n", fileName, comp_index + 1);
		comp_index++;
		fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
	}
	else if(strcmp(token, "le") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// get a
		fputs("\tLDR R1 R6 #1\n", outStream); 	// get b
		fputs("\tADD R6 R6 #1\n", outStream); 	// update SP
		fputs("\tCMP R0 R1\n", outStream); 	// a - b
		fprintf(outStream, "\tBRnz %s_comp_%d\n", fileName, comp_index);		// if negative or 0, skip next 2 lines
		fputs("\tCONST R0 #0\n", outStream);	// false, so want to return 0
		fprintf(outStream, "\tBRnzp %s_comp_%d\n", fileName, comp_index + 1);		// skip next line
		fprintf(outStream, "%s_comp_%d", fileName, comp_index);
		fputs("\tCONST R0 #1\n", outStream);	// true, so want to return 1
		fprintf(outStream, "%s_comp_%d\n", fileName, comp_index + 1);
		comp_index++;
		fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
	}
	else if(strcmp(token, "eq") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// get a
		fputs("\tLDR R1 R6 #1\n", outStream); 	// get b
		fputs("\tADD R6 R6 #1\n", outStream); 	// update SP
		fputs("\tCMP R0 R1\n", outStream); 	// a - b
		fprintf(outStream, "\tBRz %s_comp_%d\n", fileName, comp_index);		// if negative or 0, skip next 2 lines
		fputs("\tCONST R0 #0\n", outStream);	// false, so want to return 0
		fprintf(outStream, "\tBRnzp %s_comp_%d\n", fileName, comp_index + 1);		// skip next line
		fprintf(outStream, "%s_comp_%d", fileName, comp_index);
		fputs("\tCONST R0 #1\n", outStream);	// true, so want to return 1
		fprintf(outStream, "%s_comp_%d\n", fileName, comp_index + 1);
		comp_index++;
		fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
	}
	else if(strcmp(token, "gt") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// get a
		fputs("\tLDR R1 R6 #1\n", outStream); 	// get b
		fputs("\tADD R6 R6 #1\n", outStream); 	// update SP
		fputs("\tCMP R0 R1\n", outStream); 	// a - b
		fprintf(outStream, "\tBRp %s_comp_%d\n", fileName, comp_index);		// if negative or 0, skip next 2 lines
		fputs("\tCONST R0 #0\n", outStream);	// false, so want to return 0
		fprintf(outStream, "\tBRnzp %s_comp_%d\n", fileName, comp_index + 1);		// skip next line
		fprintf(outStream, "%s_comp_%d", fileName, comp_index);
		fputs("\tCONST R0 #1\n", outStream);	// true, so want to return 1
		fprintf(outStream, "%s_comp_%d\n", fileName, comp_index + 1);
		comp_index++;
		fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
	}
	else if(strcmp(token, "ge") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// get a
		fputs("\tLDR R1 R6 #1\n", outStream); 	// get b
		fputs("\tADD R6 R6 #1\n", outStream); 	// update SP
		fputs("\tCMP R0 R1\n", outStream); 	// a - b
		fprintf(outStream, "\tBRzp %s_comp_%d\n", fileName, comp_index);		// if negative or 0, skip next 2 lines
		fputs("\tCONST R0 #0\n", outStream);	// false, so want to return 0
		fprintf(outStream, "\tBRnzp %s_comp_%d\n", fileName, comp_index + 1);		// skip next line
		fprintf(outStream, "%s_comp_%d", fileName, comp_index);
		fputs("\tCONST R0 #1\n", outStream);	// true, so want to return 1
		fprintf(outStream, "%s_comp_%d\n", fileName, comp_index + 1);
		comp_index++;
		fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
	}
	else if(strcmp(token, "and") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// get top two values from stack
		fputs("\tLDR R1 R6 #1\n", outStream);
		fputs("\tAND R0 R0 R1\n", outStream);	// bitwise and them
		fputs("\tADD R6 R6 #1\n", outStream);	// update SP
		fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
	}
	else if(strcmp(token, "or") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// get top two values from stack
		fputs("\tLDR R1 R6 #1\n", outStream);
		fputs("\tOR R0 R0 R1\n", outStream);	// bitwise or them
		fputs("\tADD R6 R6 #1\n", outStream);	// update SP
		fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
	}
	else if(strcmp(token, "not") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// get top value from stack
		fputs("\tNOT R0 R0\n", outStream);		// bitwise not 
		fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
	}
	else if(strcmp(token, "drop") == 0) {
		fputs("\tADD R6 R6 #1\n", outStream);
	}
	else if(strcmp(token, "dup") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream); 	// get value at top of stack
		fputs("\tADD R6 R6 #-1\n", outStream);	// update SP
		fputs("\tSTR R0 R6 #0\n", outStream);	// push value to new stack top
	}
	else if(strcmp(token, "swap") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// load top two values
		fputs("\tLDR R1 R6 #1\n", outStream);
		fputs("\tSTR R1 R6 #0\n", outStream);	// swap and push back to stack
		fputs("\tSTR R0 R6 #1\n", outStream);
	}
	else if(strcmp(token, "rot") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream);	// load top three values
		fputs("\tLDR R1 R6 #1\n", outStream);
		fputs("\tLDR R2 R6 #2\n", outStream);
		fputs("\tSTR R0 R6 #1\n", outStream);	// rotate them and push back to stack
		fputs("\tSTR R1 R6 #2\n", outStream);
		fputs("\tSTR R2 R6 #0\n", outStream);
	}
	else if(strcmp(token, "pick") == 0) {
		fputs("\tLDR R0 R6 #0\n", outStream); 	// pop index val off top of stack
		fputs("\tADD R6 R6 #1\n", outStream);	// update SP
		fputs("\tADD R0 R0 R6\n", outStream);	// offset R6 by index value in R0
		fputs("\tLDR R0 R0 #0\n", outStream);	// load value at offset value
		fputs("\tADD R6 R6 #-1\n", outStream); // update SP 
		fputs("\tSTR R0 R6 #0\n", outStream);	// push return value to stack top
	}
	else if(strcmp(token, "if") == 0) {
		ind+=2;
		starting_index = ind;
		fputs("\tLDR R0 R6 #0\n", outStream);	// pop value off top of stack
		fputs("\tADD R6 R6 #1\n", outStream); 	// update SP
		fputs("\tCMPI R0 #0\n", outStream);	// check if top of stack was true
		fprintf(outStream, "\tBRz %s_%d\n", fileName, ind);	// if false, break to assigned label
		while(!endif) {
			readToken(inStream, token);
			if(strcmp(token, "if") == 0) {
				handleToken(inStream, outStream, token);
			}
			else if(strcmp(token, "else") == 0) {
				fprintf(outStream, "\tBRnzp %s_%d\n", fileName, starting_index + 1);
				fprintf(outStream, "%s_%d\n", fileName, starting_index);
				hasElse = 1;
			}
			else if(strcmp(token, "endif") == 0) {
				fprintf(outStream, "%s_%d\n", fileName, starting_index + hasElse);
				endif = 1;
			}
			else {
				handleToken(inStream, outStream, token);
			}
		}
	}
	else if(strcmp(token, "defun") == 0) {
		readToken(inStream, name);
		if(!isAlnumString(name)) {
			printf("Error: %s is not a valid function name. All characters in a function name must be alphanumeric.\n", name);
			exit(1);
		}
		fputs("\t.CODE\n", outStream);
		fputs("\t.FALIGN\n", outStream);
		//writes name of function to file
		fprintf(outStream, "%s\n", name);
		//prologue
		fputs("\tADD R6 R6 #-3\n", outStream);	// allocate 3 slots for FP, RA, RV
		fputs("\tSTR R7 R6 #1\n", outStream);	// save RA that was stored in R7
		fputs("\tSTR R5 R6 #0\n", outStream); 	// save caller FP that is the value of R5
		fputs("\tADD R5 R6 #0\n", outStream);	// set up local FP to begin at current stack top
	}
	else if(strcmp(token, "return") == 0) {
		//epilogue
		fputs("\tLDR R0 R6 #0\n", outStream); 	// load value from top of stack
		fputs("\tSTR R0 R5 #2\n", outStream);	// put this value into RV address
		fputs("\tADD R6 R5 #0\n", outStream);	// move top of stack back to local frame
		fputs("\tLDR R5 R6 #0\n", outStream);	// restore caller FP
		fputs("\tLDR R7 R6 #1\n", outStream);	// restore RA
		fputs("\tADD R6 R6 #2\n", outStream); 	// free RA, FP; top of stack is RV
		fputs("\tRET\n", outStream);			// return
	}
	else if(isDecimalString(token)) {
		fprintf(outStream, "\tCONST R0 #%s\n", token);
		fputs("\tSTR R0 R6 #-1\n", outStream);
		fputs("\tADD R6 R6 #-1\n", outStream);
	}
	else if(isHexString(token)) {
		fprintf(outStream, "\tCONST R0 %s\n", token);
		fputs("\tSTR R0 R6 #-1\n", outStream);
		fputs("\tADD R6 R6 #-1\n", outStream);
	}
	else if(isAlnumString(token)) {
		fprintf(outStream, "\tJSR %s\n", token); 	// Jump to function name
	}
	else {
		printf("Error: %s is not a valid token in J.\n", token);
		exit(1);
	}
	printf("%s\n", token);
}

int main(int argc, char *argv[]) {
	FILE *theJFile;
	FILE *theASMFile;
	char token[200];

	theJFile = fopen(argv[1], "r");
	fileName = malloc(strlen(argv[1]) + 2);
	strncpy(fileName, argv[1], strlen(argv[1]) - 2);
	
	theASMFile = fopen(strcat(fileName, ".asm"), "w");
	strncpy(fileName, argv[1], strlen(argv[1]) - 4);
	
	/*fputs("\t.CODE\n", theASMFile);
	fputs("\t.ADDR 0x0000\n", theASMFile);
	fputs("STACK_START .UCONST 0x7FFF\n", theASMFile);
	fputs("\tLC R6 STACK_START\n\tLC R5 STACK_START\n", theASMFile);*/

	while(!feof(theJFile)) {
		readToken(theJFile, token);
		handleToken(theJFile, theASMFile, token);
	}
	/*fputs("\t.OS\n\t.CODE\n\t.ADDR 0x8200\n\tRTI\n", theASMFile);*/
	free(fileName);
	return 0;

}