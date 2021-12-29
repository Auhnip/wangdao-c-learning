#include <stdio.h>

int main()
{
	int ans = 0;
	int input;

	for (int i = 0; i < 5; ++i)
	{
		scanf("%d", &input);
		ans ^= input;
	}
	printf("%d", ans);

	return 0;
}