#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ELEM_TYPE;

typedef struct
{
	ELEM_TYPE* array;
	size_t size;
	size_t capacity;
} ARRAY_LIST;

void init_arr(ARRAY_LIST* arr)
{
	arr->array = NULL;
	arr->size = 0;
	arr->capacity = 0;
}

static void adjust_arr(ARRAY_LIST* arr, size_t space)
{
	if (arr->size + space <= arr->capacity)
		return;
	
	size_t new_cap = (arr->capacity ? arr->capacity << 1 : 1);
	while (new_cap < arr->size + space)
		new_cap <<= 1;

	ELEM_TYPE* new_arr = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * new_cap);
	if (!new_arr)
	{
		fprintf(stderr, "bad alloc\n");
		exit(EXIT_FAILURE);
	}

	memcpy(new_arr, arr->array, arr->size * sizeof(ELEM_TYPE));

	free(arr->array);
	arr->array = new_arr;
	arr->capacity = new_cap;
}

// insert a elements: x
_Bool insert_arr(ARRAY_LIST* arr, size_t index, ELEM_TYPE x)
{
	if (index < 0 || index > arr->size)
		return 0;
	
	adjust_arr(arr, 1);

	for (int i = arr->size; i != index; --i)
		arr->array[i] = arr->array[i - 1];

	arr->array[index] = x;
	++ arr->size;
	
	return 1;
}

// insert a array: x_arr[len]
_Bool insert_arra(ARRAY_LIST* arr, size_t index, const ELEM_TYPE* x_arr, size_t len)
{
	if (index < 0 || index > arr->size)
		return 0;
	
	adjust_arr(arr, len);

	for (int i = arr->size - 1; i != index - 1; --i)
		arr->array[i + len] = arr->array[i];
	
	memcpy(arr->array + index, x_arr, len * sizeof(ELEM_TYPE));
	arr->size += len;

	return 1;
}

_Bool del_arr(ARRAY_LIST* arr, size_t index)
{
	if (index < 0 || index >= arr->size)
		return 0;
	
	for (int i = index; i != arr->size - 1; ++i)
		arr->array[i] = arr->array[i + 1];
	--arr->size;

	return 1;
}

void print_arr(const ARRAY_LIST* arr, void (*out)(const ELEM_TYPE*))
{
	for (int i = 0; i < arr->size; ++i)
		out(& arr->array[i]);
}

void print_int(const int* i)
{
	printf("%3d", *i);
}

void destroy_arr(ARRAY_LIST* arr)
{
	free(arr->array);
	arr->array = NULL;
	arr->capacity = arr->size = 0;
}

int main(void)
{
	ARRAY_LIST arr;

	int a[3] = {1, 2, 3};
	int input1, input2;

	scanf("%d %d", &input1, &input2);

	init_arr(&arr);
	insert_arra(&arr, 0, a, 3);

	insert_arr(&arr, 1, input1);
	print_arr(&arr, print_int);
	putchar('\n');

	if (del_arr(&arr, input2 - 1))
		print_arr(&arr, print_int);
	else
		printf("false\n");

	destroy_arr(&arr);

	return 0;
}