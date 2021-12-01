#include <stdio.h>

int is_leap(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int main(void)
{
	int year;

	scanf("%d", &year);
	printf("%s\n", is_leap(year) ? "yes" : "no");

	return 0;
}