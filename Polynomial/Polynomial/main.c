#include <stdio.h>
#define MAX_DEGREE 101

typedef struct{
	int degree;
	float coef[MAX_DEGREE];
}polynomial;

void padd_coef(polynomial * a, polynomial * b, polynomial * d) {
	d->degree = a->degree + b->degree;
	for (int i = 0; i <= d->degree; i++)
		d->coef[i] = a->coef[i] + b->coef[i];
}

int main(void) {
	int n = 0;
	polynomial a, b, d = { 0 };
	printf("Enter degree of A : ");
	scanf_s("%d", &a.degree);
	printf("Enter Coefficients : ");
	for (int i = 0; i <= a.degree; i++)
		scanf_s("%f", &a.coef[i]);
	printf("Enter degree of B : ");
	scanf_s("%d", &b.degree);
	printf("Enter Coefficients : ");
	for (int i = 0; i <= a.degree; i++)
		scanf_s("%f", &b.coef[i]);
	padd_coef(&a, &b, &d);
	for (int i = 0; i <= d.degree; i++)
		printf("%f", d.coef[i]);
	return 0;
}