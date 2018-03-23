#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#define MAX_SIZE 101
#define SWAP(x, y, t)  ((t = x), (x = y), (y = t));

void sort(int *list, int n); /*Selection Sort*/
int compare(int x, int y);
int binsearch(int * list, int target, int left, int right);

int main(void) {
	srand(time(NULL));
	int n = 0, temp = 0, sameness = 0, target = 0, result = 0;
	int list[MAX_SIZE] = { 0 };

	printf("Enter the number of numbers to generate : ");
	scanf_s("%d", &n);
	if (n < 1 || n > 101) {
		fprintf(stderr, "Please enter proper number (1 < n < 102)");
		Sleep(1000);
		exit(EXIT_FAILURE);
	}
	printf("Enter the target number : ");
	scanf_s("%d", &target);

	for (int i = 0; i < n; i++) {/*Randomly generate unique number list*/
		do {
			sameness = 0, temp = (rand() % 100) + 1;
			for (int j = 0; j < i; j++)
				if (temp == list[j])
					sameness = 1;
			if (sameness == 0)
				list[i] = temp;
		} while (sameness);
	}

	sort(list, n);
	result = binsearch(list, target, 0, n);
	printf("Sorted list : ");
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	if (result == -1)
		printf("\n\nThe target number do not exist");
	else
		printf("\n\nResult : [%d]", result);
	Sleep("1000");
	return 0;
}

void sort(int *list, int n) {
	int temp = 0;

	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			if (list[i] > list[j])
				SWAP(list[i], list[j], temp);
}

int compare(int x, int y) {
	if (x < y) return -1;
	else if (x == y) return 0;
	else return 1;
}

int binsearch(int * list, int target, int left, int right) {
	int middle = 0;

	while (left <= right) {
		middle = (left + right) / 2;
		switch (compare(list[middle], target)) {
		case -1: left = middle + 1;
			break;
		case 0: return middle;
		case 1: right = middle - 1;
		}
	}
	return -1;
}