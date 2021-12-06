#include <stdio.h>

int divide2(int x)
{
	return x / 2;
}

int main(void)
{
	int input;

	scanf("%d", &input);
	printf("%d\n", divide2(input));

	return 0;
}