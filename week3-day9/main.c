#include <stdio.h>
#include <string.h>

#define SIZE 256

void reverse(char *dest, const char *source)
{
	int len = 0;
	while (source[len])
		++len;

	for (int i = 0; i < len; ++i)
		dest[i] = source[len - 1 - i];

	dest[len] = '\0';
}

char *get_line(char *buff, int size)
{
	char *ret = fgets(buff, size, stdin);
	char *find = strchr(buff, '\n');
	if (ret && find)
	{
		*find = '\0';
	}
	return ret;
}

int main(void)
{
	char input[SIZE];
	char rev[SIZE];

	get_line(input, SIZE);

	reverse(rev, input);

	int cmp_ret = strcmp(input, rev);
	cmp_ret = (cmp_ret < 0 ? -1 : cmp_ret > 0);

	printf("%d\n", cmp_ret);

	return 0;
}