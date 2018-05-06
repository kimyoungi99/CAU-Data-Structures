//Header-------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Define-------------------------------------------------------------------------------------------------------

#define FALSE 0
#define TRUE 1
#define numRow 10 
#define numCol 10
#define MAXPATH 101

//Typedef------------------------------------------------------------------------------------------------------

typedef struct {
	short int vert;
	short int horiz;
}offsets;

typedef struct {
	short int row;
	short int col;
	short int dirary[8];
}element;

//Global_val---------------------------------------------------------------------------------------------------

short int maze[numRow + 2][numCol + 2];
offsets move[8] = { { -1, 0 }, { -1, 1 }, { 0, 1 },{ 1, 1 },{ 1, 0 },{ 1, -1 },{ 0, -1 },{ -1, -1 } };
element stack[MAXPATH];
int top, exit_row, exit_col;


//Function_init------------------------------------------------------------------------------------------------

void path(void);
void setup_maze(void);
element pop(void);
void push(element item);
int isdirfull(int *ary);
 
//Code---------------------------------------------------------------------------------------------------------

int main(void) {
	setup_maze();
	printf("Please Enter Target Position : ");
	scanf("%d %d", &exit_row, &exit_col);
	path();
}



void path(void) {
	srand(time(NULL));
	int row, col, nextRow, nextCol, dir, found = FALSE;
	int dirary[8];
	element position;
	maze[1][1] = 2; top = 0;
	stack[0].row = 1; stack[0].col = 1;
	for (int i = 0; i < 8; i++)
		stack[0].dirary[i] = 0;
	while (top > -1 && !found) {
		position = pop(&top);
		row = position.row;
		col = position.col;
		for (int i = 0; i < 8; i++)
			dirary[i] = position.dirary[i];
		while (!isdirfull(dirary) && !found) {
			do {
				dir = rand() % 8;
			} while (dirary[dir]);
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (((nextRow - exit_row == 1) || (nextRow - exit_row == -1)) && ((nextCol - exit_col == 1) || (nextCol - exit_col == -1)))
				found = TRUE;
			else if (!maze[nextRow][nextCol]) {
				maze[nextRow][nextCol] = 2;
				position.row = row;
				position.col = col;
				dirary[dir] = 1;
				for (int i = 0; i < 8; i++)
					position.dirary[i] = dirary[i];
				push(position);
				row = nextRow, col = nextCol;
				for (int i = 0; i < 8; i++)
					dirary[i] = 0;
			}
			else
				dirary[dir] = 1;
		}
	}
	if (found) {
		printf("The path is : \nrow  col\n");
		for (int i = 0; i <= top; i++)
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", nextRow, nextCol);
		printf("%2d%5d\n", exit_row, exit_col);
	}
	else printf("The maze does not have a path!!\n");
}

void setup_maze(void) {
	short int maze0[numRow][numCol] = {
		{ 0,0,1,0,1,1,1,0,1,0 },
		{ 1,0,0,1,1,1,0,1,0,1 },
		{ 1,1,0,1,1,0,1,0,1,1 },
		{ 0,0,1,1,1,0,1,0,0,0 },
		{ 0,1,1,1,1,0,1,0,1,0 },
		{ 1,0,1,1,0,1,1,0,1,0 },
		{ 1,1,0,1,0,1,0,0,1,0 },
		{ 1,0,1,0,1,0,1,0,0,0 },
		{ 0,1,0,1,1,1,0,1,1,0 },
		{ 1,0,0,1,1,1,0,0,0,0 }
	};
	for (int i = 0; i < numRow + 2; i++)
		for (int j = 0; j < numCol + 2; j++) {
			if (j == 0 || i == 0 || j == (numCol + 1) || i == (numRow + 1))
				maze[i][j] = 1;
			else
				maze[i][j] = maze0[i - 1][j - 1];
		}
}

element pop(void) {
	if (top == -1) {
		fprintf(stderr, "Stack is Empty, There is nothing to pop");
		exit(EXIT_FAILURE);
	}
	return stack[top--];
}

void push(element item) {
	if (top >= MAXPATH - 1) {
		fprintf(stderr, "Stack is Full, cannot add element");
		exit(EXIT_FAILURE);
	}
	stack[++top] = item;
}

int isdirfull(int *ary) {
	for (int i = 0; i < 8; i++) {
		if (ary[i] == 0)
			return FALSE;
	}
	return TRUE;
}