#include <stdio.h>

int reverse(int source)
{
	int ret = 0;
	while (source)
	{
		ret *= 10;
		ret += source % 10;
		source /= 10;
	}
	return ret;
}

int main(void)
{
	int input;

	scanf("%d", &input);
	printf("%s\n", reverse(input) == input ? "yes" : "no");

	return 0;
}