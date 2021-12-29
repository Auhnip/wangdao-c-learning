#include <stdio.h>

// print data in binary form
void print_bin(void* ptr, int size)
{
	unsigned char* p = ptr;
	while (size--)
	{
		for (int i = 7; i >= 0; --i)
		{
			if (i == 3)
				putchar(' ');
			putchar(((p[size] >> i) & 0x01) + '0');
		}
		putchar(size ? ' ' : '\n');
	}
}

int main()
{
	// float f = 1.456f;
	// print_bin(&f, sizeof(f));
	printf("  0 13");

	return 0;
}