#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

void insertion_sort(int* array, size_t size)
{
	size_t tail;
	size_t in;
	int temp;

	for (tail = 1; tail < size; ++tail)
	{
		temp = array[tail];
		for (in = tail; in > 0 && array[in - 1] > temp; --in)
		{
			array[in] = array[in - 1];
		}
		array[in] = temp;
	}
}

void quick_sort_base(int* array, int head, int tail) //[head, tail]
{
	if (head >= tail)
		return;
	
	int h = head;
	int t = tail;
	int mark = array[head];
	
	while (head != tail)
	{
		while (head != tail && array[tail] >= mark)
			--tail;
		array[head] = array[tail];

		while (head != tail && array[head] <= mark)
			++head;
		array[tail] = array[head];
	}

	array[head] = mark;

	quick_sort_base(array, h, head - 1);
	quick_sort_base(array, head + 1, t);
}

void quick_sort(int* array, size_t size)
{
	if (size <= 1)
		return;
	
	quick_sort_base(array, 0, size - 1);
}

void bubble_sort(int* array, size_t size)
{
	if (!size)
		return;
	int temp;
	for (size_t i = 0; i < size - 1; ++i)
	{
		for (size_t j = size - 1; j > i; --j)
		{
			if (array[j - 1] > array[j])
			{
				temp = array[j - 1];
				array[j - 1] = array[j];
				array[j] = temp;
			}
		}
	}
}

void print_array(int* array, int size)
{
	for (int i = 0; i < size; ++i)
		printf("%3d", array[i]);
	putchar('\n');
}

int main()
{
	int input[SIZE];
	int to_sort[SIZE];

	for (int i = 0; i < SIZE; ++i)
		scanf("%d", input + i);
	
	memcpy(to_sort, input, sizeof(input));
	bubble_sort(to_sort, SIZE);
	print_array(to_sort, SIZE);

	memcpy(to_sort, input, sizeof(input));
	quick_sort(to_sort, SIZE);
	print_array(to_sort, SIZE);

	memcpy(to_sort, input, sizeof(input));
	insertion_sort(to_sort, SIZE);
	print_array(to_sort, SIZE);

	return 0;
}