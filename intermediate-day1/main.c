#include <stdio.h>

#define SIZE 64

struct student
{
	unsigned id;
	char name[SIZE];
	char sex;
};

int main(void)
{
	struct student stu;

	scanf("%u %s %c", &stu.id, stu.name, &stu.sex);
	printf("%u %s %c", stu.id, stu.name, stu.sex);

	return 0;
}