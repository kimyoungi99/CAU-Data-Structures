#include <stdio.h>
#define numRow 10 
#define numCol 10

void setup_maze(short *(maze0[10]), short *(maze[12])) {
	for (int i = 0; i < numRow + 2; i++) {

	}
}

int main(void) {
	short maze0[numRow][numCol] = { 
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
	short maze[numRow + 2][numCol + 2] = { 0 };


}