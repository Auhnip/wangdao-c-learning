#include <stdio.h>

int main(void)
{
	int a;
	char b;
	double c;

	scanf("%d %c %lf", &a, &b, &c);
	printf("%.2f\n", a + b + c);

	return 0;
}