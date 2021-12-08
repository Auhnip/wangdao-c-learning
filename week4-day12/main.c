#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int len;

	scanf("%d", &len);

	int* ans = (int*)malloc(sizeof(int) * (len + 1));

	for (int i = 0; i != len + 1; ++i)
	{
		ans[i] = (i < 4 ? i : ans[i - 1] + ans[i - 2]);
	}
	printf("%d\n", ans[len]);

	free(ans);

	return 0;
}