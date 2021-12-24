#include <stdio.h>
#include <string.h>

#define SIZE 10

int int_cmp(int lhs, int rhs)
{
	return rhs - lhs;
}

// assume array[1...size] is a heap, move heap[pos] to right location
static void heap_adjust(int *array, int pos, int size, int (*cmp)(int, int))
{
	int temp, child;

	temp = array[pos];
	// for (child = pos * 2; child <= size; pos = child, child *= 2)
	for (child = (pos << 1); child <= size; pos = child, child <<= 1)
	{
		if (child != size && cmp(array[child + 1], array[child]) < 0)
			++child;

		if (cmp(array[child], temp) > 0)
			break;

		array[pos] = array[child];
	}
	array[pos] = temp;
}

// let [head, tail) be a heap
void heap_init(int *head, int *tail, int (*cmp)(int, int))
{
	if (head >= tail - 1)
		return;

	int *array = head - 1;
	int size = tail - head;

	for (int cur = size / 2; cur >= 1; --cur)
	{
		heap_adjust(array, cur, size, cmp);
	}
}

// assume [head, tail) is heap, pop top of heap to leaf node
void heap_pop(int* head, int* tail, int (*cmp)(int, int))
{
	int temp = *head;
	*head = *(tail - 1);
	*(tail - 1) = temp;

	heap_adjust(head - 1, 1, tail - head - 1, cmp);
}

// sort [head, tail)
void heap_sort(int* head, int* tail, int (*cmp)(int, int))
{
	heap_init(head, tail, cmp);

	while (head < tail - 1)
	{
		heap_pop(head, tail, cmp);
		--tail;
	}
}

void selection_sort(int* array, int size)
{
	int tmp, in;
	for (int i = 0; i < size - 1; ++i)
	{
		tmp = array[i];
		in = i;
		for (int j = i + 1; j < size; ++j)
		{
			if (array[i] > array[j])
			{
				array[i] = array[j];
				in = j;
			}
		}
		array[in] = tmp;
	}
}

void print_array(int* array, int size)
{
	for (int i = 0; i < size; ++i)
		printf("%3d", array[i]);
	putchar('\n');
}

int main(void)
{
	int input[SIZE];
	int to_sort[SIZE];

	for (int i = 0; i < SIZE; ++i)
		scanf("%d", input + i);
	
	memcpy(to_sort, input, sizeof(input));
	selection_sort(to_sort, SIZE);
	print_array(to_sort, SIZE);

	memcpy(to_sort, input, sizeof(input));
	heap_sort(to_sort, to_sort + SIZE, int_cmp);
	print_array(to_sort, SIZE);

	return 0;
}