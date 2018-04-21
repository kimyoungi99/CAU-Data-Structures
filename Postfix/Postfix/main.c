#include <stdio.h>
#define MAX 100

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand} precedence;
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };
char string[MAX] = { 0 };
char postfix_string[MAX] = { 0 };

//-------------------------------------------------------------------------STACK INIT
typedef struct {
	char op;
} element;
element postfix_stack[MAX];
int postfix_top = -1;

element op_stack[MAX];
int op_top = -1;
//-------------------------------------------------------------------------FUNCTION INIT
int eval(void);
precedence getToken(char *symbol, int *n);
precedence getToken_fp(char *symbol, int *n);
void stackpush(int symbol, element * stk, int top);
int stackpop(element *stk, int *top);
void postfix(void);

int main(void) {
	printf("Input Equation : ");
	gets(string);
	printf("Equation : ");
	postfix();
	puts(postfix_string);
	printf("Result : %d", eval());
 }

int eval(void) {
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	token = getToken(&symbol, &n);
	while (token != eos) {
		if (token == operand)
			stackpush(symbol - '0', op_stack, &op_top);
		else {
			op2 = stackpop(op_stack, &op_top);
			op1 = stackpop(op_stack, &op_top);
			switch (token) {
			case plus: stackpush(op1 + op2, op_stack, &op_top);
					   break;
			case minus: stackpush(op1 - op2, op_stack, &op_top);
					   break;
			case times: stackpush(op1 * op2, op_stack, &op_top);
					   break;
			case divide: stackpush(op1 / op2, op_stack, &op_top);
					   break;
			case mod: stackpush(op1 % op2, op_stack, &op_top);
					   break;
			}
		}
		token = getToken(&symbol, &n);
	}
	return stackpop(op_stack, &op_top);
}

void postfix(void) {
	char symbol;
	precedence token;
	int n = 0, i = 0;
	postfix_stack[++postfix_top].op = ' ';
	for (token = getToken_fp(&symbol, &n); token != eos; token = getToken_fp(&symbol, &n)) {
		if (token == operand)
			postfix_string[i++] = symbol;
		else if (token == rparen) {
			while (postfix_stack[postfix_top].op != '(') 
				postfix_string[i++] = (char)stackpop(postfix_stack, &postfix_top);
			stackpop(postfix_stack, &postfix_top);
		}
		else {
			while (isp[getToken_gen(postfix_stack[postfix_top].op)] >= icp[token])
				postfix_string[i++] = (char)stackpop(postfix_stack, &postfix_top);
			stackpush(symbol, postfix_stack, &postfix_top);
		}
	}
	while (postfix_top > -1)
		postfix_string[i++] = (char)stackpop(postfix_stack, &postfix_top);
	postfix_string[i++] = '\n';
}

precedence getToken_gen(char symbol) {
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case ' ': return eos;
	default: printf("FUCK");
		      return -1;
	}
}

precedence getToken_fp(char *symbol, int *n) {
	while (string[(*n)] == ' ')
		(*n)++;
	*symbol = string[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

precedence getToken(char *symbol, int *n) {
	*symbol = postfix_string[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case ' ': return eos;
	default: return operand;
	}
}

void stackpush(int symbol, element *stk, int *top) {
	if ((*top) >= (MAX - 1)) {
		printf("\nStack is FUll!");
		return;
	}
	stk[++(*top)].op = symbol;
}

int stackpop(element *stk, int *top) {
	if (*top <= -1) {
		printf("\nStack is Empty!");
		return;
	}
	return stk[(*top)--].op;
}