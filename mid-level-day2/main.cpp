#include <stdio.h>
#include <stdlib.h>

void get_space(char*& str, size_t size)
{
	str = (char*)malloc(sizeof(char) * size);
	if (!str)
		exit(EXIT_FAILURE);
}

int main(void)
{
	char* str;

	get_space(str, 100);
	fgets(str, 100, stdin);
	puts(str);

	return 0;
}