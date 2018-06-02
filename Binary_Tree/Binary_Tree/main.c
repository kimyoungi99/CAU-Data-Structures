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
	int bit_data;
}pathdata;
pathdata path = {-1, 0};
pathdata subpath = {-1, 0};

treePointer root = NULL, temp_ptr = NULL, connection_ptr;


void preorder_print(treePointer p);
void append_node(char child, char par_type, char par);
void preorder_search(treePointer p, char tar);
int find_relation(treePointer p, char tar, pathdata *pdata);
void print_relation(treePointer p);
int find_connection(pathdata t_path, pathdata t_subpath);
char find_data(pathdata pdata);
void print_relation_subpath(treePointer p);
void clear_node(treePointer p);
void push(int val, pathdata *pdata);
int pop(pathdata *pstack);
int pop_qsbit(pathdata *pq);
void reset_data();



int main(void) {
	char child, parent, par_type;
	int connectionlevel = 0;
	pathdata temppath;
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
				print_relation(temp_ptr);
			else{								//path : parent, subpath : child
				find_relation(root, parent, &path);
				find_relation(root, child, &subpath);
				connectionlevel = find_connection(path, subpath);
				if (connectionlevel == 0) {
					temppath = subpath;
					if (pop(&temppath)) {
						print_relation_subpath(connection_ptr->father);
						printf("%c-C-", connection_ptr->father->name);
					}
					else {
						print_relation_subpath(connection_ptr->mother);
						printf("%c-C-", connection_ptr->mother->name);
					}
					reset_data();
					find_relation(connection_ptr, parent, &path);
					print_relation(connection_ptr);
				}
				else {
					print_relation_subpath(connection_ptr);
					reset_data();
					find_relation(connection_ptr, parent, &path);
					print_relation(connection_ptr);
				}
			}
			puts("");
			reset_data();
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

int find_relation(treePointer p, char tar, pathdata *pdata) {
	int boolen = 0;
	if (p) {
		if (p->name == tar)
			return TRUE;
		boolen = find_relation(p->father, tar, pdata);
		if (boolen) {
			push(FATHER, pdata);
			return TRUE;
		}
		boolen = find_relation(p->mother, tar, pdata);
		if (boolen) {
			push(MOTHER, pdata);
			return TRUE;
		}
	}
	return FALSE;
}

void print_relation(treePointer p) {
	printf("%c", p->name);
	while (path.top > -1) {
		if (pop(&path)) {
			printf("-F-");
			p = p->father;
			printf("%c", p->name);
		}
		else{
			printf("-M-");
			p = p->mother;
			printf("%c", p->name);
		}
	}
}
}

int find_connection(pathdata t_path, pathdata t_subpath) {
	int temp = 0;
	connection_ptr = root;
	temp = pop(&t_path);
	if (temp != pop(&t_subpath))
		return 0;
	else {
		do {
			if (temp)
				connection_ptr = connection_ptr->father;
			else
				connection_ptr = connection_ptr->mother;
			temp = pop(&t_path);
		} while (temp == pop(&t_subpath));
	}
	return 1;
}

char find_data(pathdata pdata) {
	treePointer ntemp = root;
	while (pdata.top > -1) {
		if (pop(&pdata))
			ntemp = ntemp->father;
		else
			ntemp = ntemp->mother;
	}
	return ntemp->name;
}

void print_relation_subpath(treePointer p) {
	char temp_name = find_data(subpath);
	while (temp_name != p->name) {
		printf("%c", temp_name);
		if (pop_qsbit(&subpath) == 1) {
			printf("-S-");
		}
		else {
			printf("-D-");
		}
		temp_name = find_data(subpath);
	}
}

void clear_node(treePointer p) {
	p->name = '0';
	p->father = NULL;
	p->mother = NULL;
}

void push(int val, pathdata *pdata) {
	if (pdata->top > 31)
		printf("Stack is Full!");
	pdata->bit_data |= (val << ++(pdata->top));
}

int pop(pathdata *pstack) {
	int temp = -1, retv = 0; // temp => every bit set
	if (pstack->top < 0) {
		printf("Stack is Empty!");
		return 0;
	}
	retv = (pstack->bit_data >> pstack->top) & 1;
	temp ^= (1 << pstack->top--);
	pstack->bit_data &= temp;
	return retv;
}

int pop_qsbit(pathdata *pq) {
	int retv = 0;
	if (pq->top < 0) {
		printf("Queue is Empty!");
		return 0;
	}
	retv = pq->bit_data & 2;
	retv = retv >> 1;
	pq->bit_data = pq->bit_data >> 1;
	(pq->top)--;
	return retv;
}

void reset_data() {
	path.top = -1, path.bit_data = 0, subpath.top = -1, subpath.bit_data = 0;
}