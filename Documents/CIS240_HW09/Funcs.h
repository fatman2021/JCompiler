/* 
 * Funcs.h
 * Contains all the functions and operations performed within the J language.
 */

 void add(char *stack);
 void sub(char *stack);
 void mul(char *stack);
 void div(char *stack);
 void mod(char *stack);


 void readTokens(FILE *jFile) {
	char *stack;


	while(!feof(jFile)) {
		char *token;
		switch(token) {
			case "defun" :
			defun(stack);
			break;
			case "+" :
			arith(stack, "add");
			break;
			case "-" :
			arith(stack, "sub");
			break;
			case "*" :
			arith(stack, "mul");
			break;
			case "/" :
			arith(stack, "div");
			break;
			case "%" :
			arith(stack, "mod");
			break;
			case "lt" :
			compar(stack, "lt");
			break;
			case "le" :
			compar(stack, "le");
			break;
			case "eq" :
			compar(stack, "eq");
			break;
			case "ge" :
			compar(stack, "ge");
			break;
			case "gt" :
			compar(stack, "gt");
			break;
			case "and" :
			logic(stack, "and");
			break;
			case "or" :
			logic(stack, "or");
			break;
			case "not" :
			logic(stack, "not");
			break;
			case "drop" :
			stackOps(stack, "drop");
			break;
			case "dup" :
			stackOps(stack, "dup");
			break;
			case "swap" :
			stackOps(stack, "swap");
			break;
			case "rot" :
			stackOps(stack, "rot");
			break;
			case "pick" :
			stackOps(stack, "pick");

		}
	}
}