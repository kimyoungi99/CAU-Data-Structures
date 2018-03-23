#include <stdio.h>
#include <windows.h>

int  top[3] = { 0 };

void hanoi(int n,int * first_pole,int * target_pole, int * temp);

int main(void) {
	int top_hight = 0;
	printf("Enter hight of tower : ");
	scanf_s("%d", &top_hight);
	top[0] = top_hight;
	printf("\n\nTower\n%10d%10d%10d", top[0], top[1], top[2]);
	printf("\n\n%10d%10d%10d\n\nMovement\n", 1, 2, 3);
	hanoi(top_hight, &top[0], &top[2], &top[1]);

	printf("\n\nTower\n%10d%10d%10d", top[0], top[1], top[2]);
	printf("\n\n%10d%10d%10d\n", 1, 2, 3);
	Sleep(100000);
}

   void hanoi(int n, int * first_pole, int * target_pole, int * temp) {
	int first = 0, target = 0;

	if (n == 1) {
		(*first_pole)--, (*target_pole)++;

		if (first_pole == &top[0]) {
			first = 1;
			if (target_pole == &top[1])
				target = 2;
			else
				target = 3;
		}
		else if (first_pole == &top[1]) {
			first = 2;
			if (target_pole == &top[0])
				target = 1;
			else
				target = 3;
		}
		else if (first_pole == &top[2]) {
			first = 3;
			if (target_pole == &top[0])
				target = 1;
			else
				target = 2;
		}
		printf("%d to %d\n", first, target);
	}
	else {
		hanoi(n - 1, first_pole, temp, target_pole);
		hanoi(1, first_pole, target_pole, temp);
		hanoi(n - 1, temp, target_pole, first_pole);
	}
}