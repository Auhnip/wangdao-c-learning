#include <stdio.h>

int main()
{
	int input;

	scanf("%d", &input);

	printf("%2d\n%2d", input << 1, input >> 1);

	return 0;
}