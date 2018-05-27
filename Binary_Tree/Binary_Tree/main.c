#include <stdio.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0
#define FATHER 1
#define MOTHER 0


typedef struct node *treePointer;
typedef struct node {
	char name;
	treePointer father, mother;
}node;


typedef struct {
	int top;
	int bit_stack;
}pathstack;
pathstack path = {-1, 0};
pathstack subpath = {-1, 0};

treePointer root = NULL, temp_ptr = NULL;


void preorder_print(treePointer p);
void append_node(char child, char par_type, char par);
void preorder_search(treePointer p, char tar);
int find_relation(treePointer p, char tar, pathstack *pstack);
void print_relation();
void clear_node(treePointer p);
void push(int val, pathstack *pstack);
int pop(pathstack *pstack);



int main(void) {
	char child, parent, par_type;
	while (1) {
		printf(">>");
		scanf("%c-%c-%c", &child, &par_type, &parent);
		while (getchar() != '\n');
		if (par_type == 'F' || par_type == 'M') {
			append_node(child, par_type, parent);
			preorder_print(root);
			puts("");
		}
		else if (par_type == '?') {
			preorder_search(root, child);
			find_relation(temp_ptr, parent, &path);
			if (path.top != -1)
				print_relation();
			else{								//path : parent, subpath : child
				
			}
			puts("");
		}
		else
			printf("Worng Data!\n");
	}
	return 0;
}

void preorder_print(treePointer p) {
	if (p) {
		printf("%c", p->name);
		preorder_print(p->father);
		preorder_print(p->mother);
	}
}

void preorder_search(treePointer p, char tar) {
	if (p) {
		if (p->name == tar)
			temp_ptr = p;
		preorder_search(p->father, tar);
		preorder_search(p->mother, tar);
	}
}


void append_node(char child, char par_type, char par) {
	if (root == NULL) {
		root = (node *)malloc(sizeof(node));
		clear_node(root);
		if (par_type == 'F') {
			root->name = child;
			root->father = (node *)malloc(sizeof(node));
			clear_node(root->father);
			root->father->name = par;
		}
		else {
			root->name = child;
			root->mother = (node *)malloc(sizeof(node));
			clear_node(root->mother);
			root->mother->name = par;
		}
	}
	else if (root->name == par) {
		treePointer temp = (node *)malloc(sizeof(node));
		clear_node(temp);
		if (par_type == 'F') {
			temp->father = root;
			root = temp;
			root->name = child;
		}
		else {
			temp->mother = root;
			root = temp;
			root->name = child;
		}
	}
	else {
		preorder_search(root, child);
		if (par_type == 'F') {
			temp_ptr->father = (node *)malloc(sizeof(node));
			clear_node(temp_ptr->father);
			temp_ptr->father->name = par;
		}
		else {
			temp_ptr->mother = (node *)malloc(sizeof(node));
			clear_node(temp_ptr->mother);
			temp_ptr->mother->name = par;
		}
	}
}

int find_relation(treePointer p, char tar, pathstack *pstack) {
	int boolen = 0;
	if (p) {
		if (p->name == tar)
			return TRUE;
		boolen = find_relation(p->father, tar, pstack);
		if (boolen) {
			push(FATHER, pstack);
			return TRUE;
		}
		boolen = find_relation(p->mother, tar, pstack);
		if (boolen) {
			push(MOTHER, pstack);
			return TRUE;
		}
	}
	return FALSE;
}

void print_relation() {
	printf("%c", temp_ptr->name);
	while (path.top > -1) {
		if (pop(&path)) {
			printf("-F-");
			temp_ptr = temp_ptr->father;
			printf("%c", temp_ptr->name);
		}
		else{
			printf("-M-");
			temp_ptr = temp_ptr->mother;
			printf("%c", temp_ptr->name);
		}
	}
}

void clear_node(treePointer p) {
	p->name = '0';
	p->father = NULL;
	p->mother = NULL;
}

void push(int val, pathstack *pstack) {
	if (pstack->top > 31)
		printf("Stack is Full!");
	pstack->bit_stack |= (val << ++(pstack->top));
}

int pop(pathstack *pstack) {
	int temp = -1, retv = 0; // temp => every bit set
	if (pstack->top < 0)
		printf("Stack is Empty!");
	retv = (pstack->bit_stack >> pstack->top) & 1;
	temp ^= (1 << pstack->top--);
	pstack->bit_stack &= temp;
	return retv;
}