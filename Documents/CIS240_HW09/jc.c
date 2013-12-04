#include <stdio.h>
#include <string.h>
#include <ctype.h>




//name could also be a char * i think
// function ops
void defun(FILE *stream, char[] name) {
	fputs("\t.CODE\n", stream);
	fputs("\t.FALIGN\n", stream);
	//writes name of function to file
	fprintf(stream, "%s\n", name);
	//prologue
	fputs("\tADD R6 R6 #-3\n", stream);	// allocate 3 slots for FP, RA, RV
	fputs("\tSTR R7 R6 #1\n", stream);	// save RA that was stored in R7
	fputs("\tSTR R5 R6 #0\n", stream); 	// save caller FP that is the value of R5
	fputs("\tADD R5 R6 #0\n", stream);	// set up local FP to begin at current stack top
}	
void funCall(FILE *stream, char[] name) {
	fprintf(stream, "\tJSR %s\n", name); 	// Jump to function name
}
void ret(FILE *stream) {
	//epilogue
	fputs("\tLDR R0 R6 #0\n", stream); 	// load value from top of stack
	fputs("\tSTR R0 R5 #2\n", stream);	// put this value into RV address
	fputs("\tADD R6 R5 #0\n", stream);	// move top of stack back to loval frame
	fputs("\tLDR R5 R6 #0\n", stream);	// restore caller FP
	fputs("\tLDR R7 R6 #1\n", stream);	// restore RA
	fputs("\tADD R6 R6 #3\n", stream); 	// free RA, RV, FP
}
// arithmetic ops
void add(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// get values off top of stack
	fputs("\tLDR R1 R6 #1\n", stream);
	fputs("\tADD R0 R0 R1\n", stream);	// add and store in R0
	fputs("\tADD R6 R6 #1\n", stream);	// update SP
	fputs("\tSTR R0 R6 #0\n", stream); 	// push return value onto top of stack
}
void sub(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// get values off top of stack
	fputs("\tLDR R1 R6 #1\n", stream);
	fputs("\tSUB R0 R0 R1\n", stream);	// subtract and store in R0
	fputs("\tADD R6 R6 #1\n", stream);	// update SP
	fputs("\tSTR R0 R6 #0\n", stream); 	// push return value onto top of stack
}
void mul(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// get values off top of stack
	fputs("\tLDR R1 R6 #1\n", stream);
	fputs("\tMUL R0 R0 R1\n", stream);	// multiply and store in R0
	fputs("\tADD R6 R6 #1\n", stream);	// update SP
	fputs("\tSTR R0 R6 #0\n", stream); 	// push return value onto top of stack
}
void div(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// get values off top of stack
	fputs("\tLDR R1 R6 #1\n", stream);
	fputs("\tDIV R0 R0 R1\n", stream);	// divide and store in R0
	fputs("\tADD R6 R6 #1\n", stream);	// update SP
	fputs("\tSTR R0 R6 #0\n", stream); 	// push return value onto top of stack
}
void mod(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// get values off top of stack
	fputs("\tLDR R1 R6 #1\n", stream);
	fputs("\tMOD R0 R0 R1\n", stream);	// mod and store in R0
	fputs("\tADD R6 R6 #1\n", stream);	// update SP
	fputs("\tSTR R0 R6 #0\n", stream); 	// push return value onto top of stack
}
// comparisons
void lt(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// get a
	fputS("\tLDR R1 R6 #1\n", stream); 	// get b
	fputs("\tCMP R0 R1\n", stream); 	// a - b
	fputS("\tADD R6 R6 #1\n", stream); 	// update SP
	fputs("\tBRn #2\n", stream);		// if negative, skip next 2 lines
	fputs("\tCONST R0 #0\n", stream);	// false, so want to return 0
	fputs("\tBRnzp #1\n", stream);		// skip next line
	fputs("\tCONST R0 #1\n", stream);	// true, so want to return 1
	fputs("\tSTR R0 R6 #0\n", stream); 	// push return value on top of stack
}
void le(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// get a
	fputS("\tLDR R1 R6 #1\n", stream); 	// get b
	fputs("\tCMP R0 R1\n", stream); 	// a - b
	fputS("\tADD R6 R6 #1\n", stream); 	// update SP
	fputs("\tBRnz #2\n", stream);		// if negative or 0, skip next 2 lines
	fputs("\tCONST R0 #0\n", stream);	// false, so want to return 0
	fputs("\tBRnzp #1\n", stream);		// skip next line
	fputs("\tCONST R0 #1\n", stream);	// true, so want to return 1
	fputs("\tSTR R0 R6 #0\n", stream); 	// push return value on top of stack
}
void eq(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// get a
	fputS("\tLDR R1 R6 #1\n", stream); 	// get b
	fputs("\tCMP R0 R1\n", stream); 	// a - b
	fputS("\tADD R6 R6 #1\n", stream); 	// update SP
	fputs("\tBRz #2\n", stream);		// if 0, skip next 2 lines
	fputs("\tCONST R0 #0\n", stream);	// false, so want to return 0
	fputs("\tBRnzp #1\n", stream);		// skip next line
	fputs("\tCONST R0 #1\n", stream);	// true, so want to return 1
	fputs("\tSTR R0 R6 #0\n", stream); 	// push return value on top of stack
}
void ge(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// get a
	fputS("\tLDR R1 R6 #1\n", stream); 	// get b
	fputs("\tCMP R0 R1\n", stream); 	// a - b
	fputS("\tADD R6 R6 #1\n", stream); 	// update SP
	fputs("\tBRzp #2\n", stream);		// if positive or 0, skip next 2 lines
	fputs("\tCONST R0 #0\n", stream);	// false, so want to return 0
	fputs("\tBRnzp #1\n", stream);		// skip next line
	fputs("\tCONST R0 #1\n", stream);	// true, so want to return 1
	fputs("\tSTR R0 R6 #0\n", stream); 	// push return value on top of stack
}
void gt(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// get a
	fputS("\tLDR R1 R6 #1\n", stream); 	// get b
	fputs("\tCMP R0 R1\n", stream); 	// a - b
	fputS("\tADD R6 R6 #1\n", stream); 	// update SP
	fputs("\tBRp #2\n", stream);		// if positive, skip next 2 lines
	fputs("\tCONST R0 #0\n", stream);	// false, so want to return 0
	fputs("\tBRnzp #1\n", stream);		// skip next line
	fputs("\tCONST R0 #1\n", stream);	// true, so want to return 1
	fputs("\tSTR R0 R6 #0\n", stream); 	// push return value on top of stack
}
// logic ops
void and(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// get top two values from stack
	fputs("\tLDR R1 R6 #1\n", stream);
	fputs("\tAND R0 R0 R1\n", stream);	// bitwise and them
	fputs("\tADD R6 R6 #1\n", stream);	// update SP
	fputs("\tSTR R0 R6 #0\n", stream); 	// push return value on top of stack
}
void or(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// get top two values from stack
	fputs("\tLDR R1 R6 #1\n", stream);
	fputs("\tOR R0 R0 R1\n", stream);	// bitwise or them
	fputs("\tADD R6 R6 #1\n", stream);	// update SP
	fputs("\tSTR R0 R6 #0\n", stream); 	// push return value on top of stack
}
void not(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// get top value from stack
	fputs("\tNOT R0 R0\n", stream);		// bitwise not 
	fputs("\tSTR R0 R6 #0\n", stream); 	// push return value on top of stack
}
// stack ops
void drop(FILE *stream) {
	fputs("\tADD R6 R6 #1\n", stream);
}
void dup(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream); 	// get value at top of stack
	fputs("\tADD R6 R6 #-1\n", stream);	// update SP
	fputs("\tSTR R0 R6 #0\n", stream);	// push value to new stack top
}
void swap(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// load top two values
	fputs("\tLDR R1 R6 #1\n", stream);
	fputs("\tSTR R1 R6 #0\n", stream);	// swap and push back to stack
	fputs("\tSTR R0 R6 #1\n", stream);
}
void rot(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream);	// load top three values
	fputs("\tLDR R1 R6 #1\n", stream);
	fputs("\tLDR R2 R6 #2\n", stream);
	fputs("\tSTR R0 R6 #1\n", stream);	// rotate them and push back to stack
	fputs("\tSTR R1 R6 #2\n", stream);
	fputs("\tSTR R2 R6 #0\n", stream);
}
void pick(FILE *stream) {
	fputs("\tLDR R0 R6 #0\n", stream); 	// pop index val off top of stack
	fputs("\tADD R6 R6 #1\n", stream);	// update SP
	fputs("\tADD R0 R0 R6\n", stream);	// offset R6 by index value in R0
	fputs("\tLDR R0 R0 #0\n", stream);	// load value at offset value
	fputs("\tADD R6 R6 #-1\n", stream); // update SP 
	fputs("\tSTR R0 R6 #0\n", stream);	// push return value to stack top
}

int main(int argc, char *argv[]) {
	FILE *theJFile;
	FILE *theASMFile;
	char *name;

	theJFile = fopen(argv[1], "r");
	//name = strrchr(argv[1], '.');
	//need to read in name of file preceding .j so that the .asm file can have the same name


	readTokens(theJFile);

}