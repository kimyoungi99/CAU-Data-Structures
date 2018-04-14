#include <stdio.h>
#define MAX 101

typedef struct {
	int value1;
}element;


//for Stack =================================================

void push(element *s, element item, int *top) {
	if ((*top) >= MAX - 1) {
		printf("Stack is Full!\n");
		return;
	}
	s[++(*top)] = item;
}

void pop(int *top) {
	if (*top == -1) {
		printf("Stack is Empty!\n");
		return;
	}
	(*top)--;
}


//for Queue=====================================================



int main(void) {
	element stack_one[MAX];
	element cur;
	int top_one = -1;
	for (int i = 0; i < 10; i++) {
		cur.value1 = i;
		push(stack_one, cur, &top_one);
	}
	pop(&top_one);
	for (int i = 0; i <= top_one; i++)
		printf("%3d", stack_one[i].value1);

}