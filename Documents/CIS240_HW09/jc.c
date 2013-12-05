#include <stdio.h>
#include <string.h>
#include <ctype.h>


//int label_tracker = 0;

//name could also be a char * i think
// function ops
void defun(FILE *outStream, char[] name) {
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
void funCall(FILE *outStream, char[] name) {
	fprintf(outStream, "\tJSR %s\n", name); 	// Jump to function name
}
void ret(FILE *outStream) {
	//epilogue
	fputs("\tLDR R0 R6 #0\n", outStream); 	// load value from top of stack
	fputs("\tSTR R0 R5 #2\n", outStream);	// put this value into RV address
	fputs("\tADD R6 R5 #0\n", outStream);	// move top of stack back to local frame
	fputs("\tLDR R5 R6 #0\n", outStream);	// restore caller FP
	fputs("\tLDR R7 R6 #1\n", outStream);	// restore RA
	fputs("\tADD R6 R6 #2\n", outStream); 	// free RA, FP; top of stack is RV
	fputs("\tRET\n", outStream);			// return
}
// push a decimal value to the top of the stack
void pushDecimal(FILE *outStream, char *i) {
	fprintf(outStream, "\tCONST R0 #%s\n", i);
	fputs("\tSTR R0 R6 #-1\n", outStream);
	fputs("\tADD R6 R6 #-1\n", outStream);
}
// push a hex value to the stack
void pushHex(FILE *outStream, char *h) {
	fprintf(outStream, "\tCONST R0 %s\n", h);
	fputs("\tSTR R0 R6 #-1\n", outStream);
	fputs("\tADD R6 R6 #-1\n", outStream);
}
// arithmetic ops
void add(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// get values off top of stack
	fputs("\tLDR R1 R6 #1\n", outStream);
	fputs("\tADD R0 R0 R1\n", outStream);	// add and store in R0
	fputs("\tADD R6 R6 #1\n", outStream);	// update SP
	fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value onto top of stack
}
void sub(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// get values off top of stack
	fputs("\tLDR R1 R6 #1\n", outStream);
	fputs("\tSUB R0 R0 R1\n", outStream);	// subtract and store in R0
	fputs("\tADD R6 R6 #1\n", outStream);	// update SP
	fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value onto top of stack
}
void mul(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// get values off top of stack
	fputs("\tLDR R1 R6 #1\n", outStream);
	fputs("\tMUL R0 R0 R1\n", outStream);	// multiply and store in R0
	fputs("\tADD R6 R6 #1\n", outStream);	// update SP
	fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value onto top of stack
}
void div(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// get values off top of stack
	fputs("\tLDR R1 R6 #1\n", outStream);
	fputs("\tDIV R0 R0 R1\n", outStream);	// divide and store in R0
	fputs("\tADD R6 R6 #1\n", outStream);	// update SP
	fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value onto top of stack
}
void mod(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// get values off top of stack
	fputs("\tLDR R1 R6 #1\n", outStream);
	fputs("\tMOD R0 R0 R1\n", outStream);	// mod and store in R0
	fputs("\tADD R6 R6 #1\n", outStream);	// update SP
	fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value onto top of stack
}
// comparisons
void lt(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// get a
	fputS("\tLDR R1 R6 #1\n", outStream); 	// get b
	fputs("\tCMP R0 R1\n", outStream); 	// a - b
	fputS("\tADD R6 R6 #1\n", outStream); 	// update SP
	fputs("\tBRn #2\n", outStream);		// if negative, skip next 2 lines
	fputs("\tCONST R0 #0\n", outStream);	// false, so want to return 0
	fputs("\tBRnzp #1\n", outStream);		// skip next line
	fputs("\tCONST R0 #1\n", outStream);	// true, so want to return 1
	fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
}
void le(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// get a
	fputS("\tLDR R1 R6 #1\n", outStream); 	// get b
	fputs("\tCMP R0 R1\n", outStream); 	// a - b
	fputS("\tADD R6 R6 #1\n", outStream); 	// update SP
	fputs("\tBRnz #2\n", outStream);		// if negative or 0, skip next 2 lines
	fputs("\tCONST R0 #0\n", outStream);	// false, so want to return 0
	fputs("\tBRnzp #1\n", outStream);		// skip next line
	fputs("\tCONST R0 #1\n", outStream);	// true, so want to return 1
	fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
}
void eq(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// get a
	fputS("\tLDR R1 R6 #1\n", outStream); 	// get b
	fputs("\tCMP R0 R1\n", outStream); 	// a - b
	fputS("\tADD R6 R6 #1\n", outStream); 	// update SP
	fputs("\tBRz #2\n", outStream);		// if 0, skip next 2 lines
	fputs("\tCONST R0 #0\n", outStream);	// false, so want to return 0
	fputs("\tBRnzp #1\n", outStream);		// skip next line
	fputs("\tCONST R0 #1\n", outStream);	// true, so want to return 1
	fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
}
void ge(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// get a
	fputS("\tLDR R1 R6 #1\n", outStream); 	// get b
	fputs("\tCMP R0 R1\n", outStream); 	// a - b
	fputS("\tADD R6 R6 #1\n", outStream); 	// update SP
	fputs("\tBRzp #2\n", outStream);		// if positive or 0, skip next 2 lines
	fputs("\tCONST R0 #0\n", outStream);	// false, so want to return 0
	fputs("\tBRnzp #1\n", outStream);		// skip next line
	fputs("\tCONST R0 #1\n", outStream);	// true, so want to return 1
	fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
}
void gt(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// get a
	fputS("\tLDR R1 R6 #1\n", outStream); 	// get b
	fputs("\tCMP R0 R1\n", outStream); 	// a - b
	fputS("\tADD R6 R6 #1\n", outStream); 	// update SP
	fputs("\tBRp #2\n", outStream);		// if positive, skip next 2 lines
	fputs("\tCONST R0 #0\n", outStream);	// false, so want to return 0
	fputs("\tBRnzp #1\n", outStream);		// skip next line
	fputs("\tCONST R0 #1\n", outStream);	// true, so want to return 1
	fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
}
// logic ops
void and(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// get top two values from stack
	fputs("\tLDR R1 R6 #1\n", outStream);
	fputs("\tAND R0 R0 R1\n", outStream);	// bitwise and them
	fputs("\tADD R6 R6 #1\n", outStream);	// update SP
	fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
}
void or(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// get top two values from stack
	fputs("\tLDR R1 R6 #1\n", outStream);
	fputs("\tOR R0 R0 R1\n", outStream);	// bitwise or them
	fputs("\tADD R6 R6 #1\n", outStream);	// update SP
	fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
}
void not(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// get top value from stack
	fputs("\tNOT R0 R0\n", outStream);		// bitwise not 
	fputs("\tSTR R0 R6 #0\n", outStream); 	// push return value on top of stack
}
// stack ops
void drop(FILE *outStream) {
	fputs("\tADD R6 R6 #1\n", outStream);
}
void dup(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream); 	// get value at top of stack
	fputs("\tADD R6 R6 #-1\n", outStream);	// update SP
	fputs("\tSTR R0 R6 #0\n", outStream);	// push value to new stack top
}
void swap(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// load top two values
	fputs("\tLDR R1 R6 #1\n", outStream);
	fputs("\tSTR R1 R6 #0\n", outStream);	// swap and push back to stack
	fputs("\tSTR R0 R6 #1\n", outStream);
}
void rot(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// load top three values
	fputs("\tLDR R1 R6 #1\n", outStream);
	fputs("\tLDR R2 R6 #2\n", outStream);
	fputs("\tSTR R0 R6 #1\n", outStream);	// rotate them and push back to stack
	fputs("\tSTR R1 R6 #2\n", outStream);
	fputs("\tSTR R2 R6 #0\n", outStream);
}
void pick(FILE *outStream) {
	fputs("\tLDR R0 R6 #0\n", outStream); 	// pop index val off top of stack
	fputs("\tADD R6 R6 #1\n", outStream);	// update SP
	fputs("\tADD R0 R0 R6\n", outStream);	// offset R6 by index value in R0
	fputs("\tLDR R0 R0 #0\n", outStream);	// load value at offset value
	fputs("\tADD R6 R6 #-1\n", outStream); // update SP 
	fputs("\tSTR R0 R6 #0\n", outStream);	// push return value to stack top
}
// if statement handling
/*void ifHandling(FILE *outStream, char[] name) {
	fputs("\tLDR R0 R6 #0\n", outStream);	// pop value off top of stack
	fputs("\tADD R6 R6 #1\n", outStream); 	// update SP
	fputs("\tCMPI R0 #0\n", outStream);	// check if top of stack was true
	fprintf(outStream, "\tBRz %s_%d\n", name, label_tracker);	// if false, break to assigned label
	//fprintf(outStream, "%s_%d\n", name, label_tracker);
}*/
// checks if null-terminated string is made up of all alpha-numeric characters
// returns 1 if it is and 0 if not
int isAlnumString(char *str) {
	while(*str != NULL) {
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
	if(*str != NULL && (*str == '-') {
		str++;
	}
	while(*str != NULL) {
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
	if(*str == NULL || (*str != '0')) {
		return 0;
	}
	str++;
	if(*str == NULL || *str != 'x') {
		return 0;
	}
	str++;
	while(*str != NULL) {
		if(!isxdigit(*str)) {
			return 0;
		}
		str++;
	}
	return 1;

}

void readToken(FILE *inStream, char *token) {
	char c = fgetc(inStream);
	// skip over all the whitespace before token
	while(c!=EOF && isspace(c)) {
		c = fgetc(inStream);
	}
	// build token
	while(c!=EOF && !isspace(c)) {
		*token = c;
		token++;
		c = fgetc(inStream);
	}
	// make token null-terminating
	*token = NULL;
}
void handleToken(FILE *inStream, FILE *outStream, char *token) {
	int n;
	char name[200];
	if(strcmp(token, "+") == 0) {
		add(outStream);
	}
	if(strcmp(token, "-") == 0) {
		sub(outStream);
	}
	if(strcmp(token, "*") == 0) {
		mul(outStream);
	}
	if(strcmp(token, "/") == 0) {
		div(outStream);
	}
	if(strcmp(token, "%") == 0) {
		mod(outStream);
	}
	if(strcmp(token, "lt") == 0) {
		lt(outStream);
	}
	if(strcmp(token, "le") == 0) {
		le(outStream);
	}
	if(strcmp(token, "eq") == 0) {
		eq(outStream);
	}
	if(strcmp(token, "gt") == 0) {
		gt(outStream);
	}
	if(strcmp(token, "ge") == 0) {
		ge(outStream);
	}
	if(strcmp(token, "and") == 0) {
		and(outStream);
	}
	if(strcmp(token, "or") == 0) {
		or(outStream);
	}
	if(strcmp(token, "not") == 0) {
		not(outStream);
	}
	if(strcmp(token, "drop") == 0) {
		drop(outStream);
	}
	if(strcmp(token, "dup") == 0) {
		dup(outStream);
	}
	if(strcmp(token, "swap") == 0) {
		swap(outStream);
	}
	if(strcmp(token, "rot") == 0) {
		rot(outStream);
	}
	if(strcmp(token, "pick") == 0) {
		pick(outStream);
	}
	if(strcmp(token, "defun") == 0) {
		readToken(inStream, name);
		if(!isAlnumString(name)) {
			printf("Error: %s is not a valid function name. All characters in a function name must be alphanumeric.\n", name);
		}
		defun(outStream, name);
	}
	if(isDecimalString(token)) {
		pushDecimal(outStream, token);
	}
	if(isHexString(token)) {
		pushHex(outStream, token);
	}


}

int main(int argc, char *argv[]) {
	FILE *theJFile;
	FILE *theASMFile;
	char *name;
	char token[200];

	theJFile = fopen(argv[1], "r");
	//name = strrchr(argv[1], '.');
	//need to read in name of file preceding .j so that the .asm file can have the same name
	theASMFile = fopen(argv[2], "w");

	while(!feof(theJFile)) {
		readToken(theJFile, token);
		handleToken(theJFile, theASMFile, token);
	}
}