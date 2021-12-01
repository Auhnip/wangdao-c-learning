#include <stdio.h>

int main(void)
{
	int n;
	int ans = 1;
	
	scanf ("%d", &n);
	while (n)
	{
		ans *= n--;
	}
	printf("%d", ans);

	return 0;
}