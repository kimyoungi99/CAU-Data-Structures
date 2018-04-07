#include <stdio.h>
#define MAX_TERMS 101

typedef struct {
	int col;
	int row;
	int value;
}term;

void transpose_one(term a[], term b[]) {
	int curb;
	b[0].row = a[0].col;
	b[0].col = a[0].row;
	b[0].value = a[0].value;
	if (b[0].value > 0) {
		curb = 1;
		for(int i = 0; i < a[0].col; i++)
			for(int j = 0; j <= b[0].value; j++)
				if (a[j].col == i) {
					b[curb].row = a[j].col;
					b[curb].col = a[j].row;
					b[curb].value = a[j].value;
					curb++;
				}
	}
 }

term * transpose_two(term * a, term * b) {

}

int main(void) {
	term a[MAX_TERMS], b[MAX_TERMS];
	a[0].row = 4, a[0].col = 3, a[0].value = 5;
	a[1].row = 0, a[1].col = 0, a[1].value = 5;
	a[2].row = 1, a[2].col = 1, a[2].value = 2;
	a[3].row = 2, a[3].col = 1, a[3].value = 1;
	a[4].row = 3, a[4].col = 0, a[4].value = 7;
	a[5].row = 3, a[5].col = 2, a[5].value = 4;		//matrix gen

	transpose_one(a, b);

	for (int i = 0; i <= b[0].value; i++)
		printf("%4d%4d%4d\n", b[i].row, b[i].col, b[i].value);
}