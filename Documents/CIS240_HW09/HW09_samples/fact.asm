	.CODE
	.FALIGN
fact
	ADD R6 R6 #-3
	STR R7 R6 #1
	STR R5 R6 #0
	ADD R5 R6 #0
	CONST R0 #3
	STR R0 R6 #-1
	ADD R6 R6 #-1
	LDR R0 R6 #0
	ADD R6 R6 #1
	ADD R0 R0 R6
	LDR R0 R0 #0
	ADD R6 R6 #-1
	STR R0 R6 #0
	LDR R0 R6 #0
	ADD R6 R6 #-1
	STR R0 R6 #0
	CONST R0 #1
	STR R0 R6 #-1
	ADD R6 R6 #-1
	LDR R0 R6 #0
	LDR R1 R6 #1
	ADD R6 R6 #1
	CMP R0 R1
	BRzp fact_comp_0
	CONST R0 #0
	BRnzp fact_comp_1
fact_comp_0
	CONST R0 #1
fact_comp_1
	STR R0 R6 #0
	LDR R0 R6 #0
	ADD R6 R6 #1
	CMPI R0 #0
	BRz fact_2
	CONST R0 #1
	STR R0 R6 #-1
	ADD R6 R6 #-1
	BRnzp fact_3
fact_2
	LDR R0 R6 #0
	ADD R6 R6 #-1
	STR R0 R6 #0
	CONST R0 #1
	STR R0 R6 #-1
	ADD R6 R6 #-1
	LDR R0 R6 #0
	LDR R1 R6 #1
	STR R1 R6 #0
	STR R0 R6 #1
	LDR R0 R6 #0
	LDR R1 R6 #1
	SUB R0 R0 R1
	ADD R6 R6 #1
	STR R0 R6 #0
	JSR fact
	LDR R0 R6 #0
	LDR R1 R6 #1
	STR R1 R6 #0
	STR R0 R6 #1
	ADD R6 R6 #1
	LDR R0 R6 #0
	LDR R1 R6 #1
	MUL R0 R0 R1
	ADD R6 R6 #1
	STR R0 R6 #0
fact_3
	LDR R0 R6 #0
	STR R0 R5 #2
	ADD R6 R5 #0
	LDR R5 R6 #0
	LDR R7 R6 #1
	ADD R6 R6 #2
	RET
	.CODE
	.FALIGN
main
	ADD R6 R6 #-3
	STR R7 R6 #1
	STR R5 R6 #0
	ADD R5 R6 #0
	CONST R0 #4
	STR R0 R6 #-1
	ADD R6 R6 #-1
	JSR fact
	JSR printnum
	JSR endl
	CONST R0 #5
	STR R0 R6 #-1
	ADD R6 R6 #-1
	JSR fact
	JSR printnum
	JSR endl
	CONST R0 #6
	STR R0 R6 #-1
	ADD R6 R6 #-1
	JSR fact
	JSR printnum
	JSR endl
	CONST R0 #7
	STR R0 R6 #-1
	ADD R6 R6 #-1
	JSR fact
	JSR printnum
	JSR endl
	LDR R0 R6 #0
	STR R0 R5 #2
	ADD R6 R5 #0
	LDR R5 R6 #0
	LDR R7 R6 #1
	ADD R6 R6 #2
	RET