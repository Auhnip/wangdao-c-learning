#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_line(char *buff, int size)
{
	char *ret = fgets(buff, size, stdin);
	char *find;
	int ch;

	if (ret)
	{
		find = strchr(buff, '\n');
		if (find)
		{
			*find = '\0';
		}
		else
		{
			while (ch = getchar(), ~ch && ch != '\n')
				continue;
		}
	}

	return ret;
}

int main(void)
{
	unsigned size;

	scanf("%u", &size);

	char* line = (char*)malloc(sizeof(char) * size);
	while (getchar() != '\n')
		continue;

	get_line(line, size);
	puts(line);

	free(line);

	return 0;
}