#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#define MAX_SIZE 101
#define SWAP(x, y, t)  ((t = x), (x = y), (y = t));

void sort(int *list, int n); /*Selection Sort*/

int main(void) {
	srand(time(NULL));
	int n = 0;
	int list[MAX_SIZE];

	printf("Enter the number of numbers to generate : ");
	scanf_s("%d", &n);
	if (n < 1 || n > 101) {
		fprintf(stderr, "Please enter proper number (1 < n < 102)");
		Sleep(1000);
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < n; i++) /*Randomly generate  number*/
		list[i] = rand() % 1000 + 1;

	printf("Randomly generated array : ");
	for (int i = 0; i < n; i++)
		printf("%d  ", list[i]);

	sort(list, n);

	printf("\nSorted array :             ");
	for (int i = 0; i < n; i++)
		printf("%d  ", list[i]);
	Sleep(10000);
	return 0;
}

void sort(int *list, int n) {
	int temp = 0;

	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			if (list[i] > list[j])
				SWAP(list[i], list[j], temp);
}