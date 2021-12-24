#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

void merge(int* arr, int* tmp_arr, const int head, const int mid, const int tail)
{
	int cur = head;
	int head1 = head, head2 = mid;
	int tail1 = mid - 1, tail2 = tail;

	while (head1 <= tail1 && head2 <= tail2)
	{
		if (arr[head1] < arr[head2])
			tmp_arr[cur++] = arr[head1++];
		else
			tmp_arr[cur++] = arr[head2++];
	}

	while (head1 <= tail1)
		tmp_arr[cur++] = arr[head1++];
	
	while (head2 <= tail2)
		tmp_arr[cur++] = arr[head2++];
	
	memcpy(arr + head, tmp_arr + head, sizeof(int) * (tail - head + 1));
}

void merge_sort_base(int* arr, int* tmp_arr, int head, int tail)
{
	if (head >= tail)
		return;
	
	int mid = (head + tail) / 2;
	merge_sort_base(arr, tmp_arr, head, mid);
	merge_sort_base(arr, tmp_arr, mid + 1, tail);
	merge(arr, tmp_arr, head, mid + 1, tail);
}

void merge_sort(int* array, size_t size)
{
	if (!size)
		return;
	
	int* tmp_arr = (int*)malloc(sizeof(int) * size);

	if (!tmp_arr)
	{
		fprintf(stderr, "no memory\n");
	}
	else
	{
		merge_sort_base(array, tmp_arr, 0, size - 1);
		free(tmp_arr);
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
	merge_sort(to_sort, SIZE);
	print_array(to_sort, SIZE);

	return 0;
}