#include <stdio.h>

int main(void)
{
	int n;
	int count = 0;
	int digit;

	scanf("%d", &n);
	while (n--)
	{
		scanf("%d", &digit);
		count += (digit == 2);
	}

	printf("%d", count);

	return 0;
}