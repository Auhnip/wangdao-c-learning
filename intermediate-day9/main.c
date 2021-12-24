#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 10

typedef struct tree_node
{
	int data;
	struct tree_node* left;
	struct tree_node* right;
} TREE_NODE, * TREE;

void tree_init(TREE* tree)
{
	*tree = NULL;
}

static TREE_NODE* create_new_node(const int x)
{
	TREE_NODE* ret = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	if (!ret)
	{
		fprintf(stderr, "no memory\n");
		exit(EXIT_FAILURE);
	}
	ret->data = x;
	ret->left = ret->right = NULL;
	return ret;
}

_Bool tree_insert(TREE* tree, const int x)
{
	if (!*tree)
	{
		*tree = create_new_node(x);
		return 1;
	}

	if (x < (*tree)->data)
	{
		return tree_insert(& (*tree)->left, x);
	}
	else if (x > (*tree)->data)
	{
		return tree_insert(& (*tree)->right, x);
	}

	return 0;
}

void tree_copy_base(const TREE_NODE* root, int* dest, int* size)
{
	if (!root)
		return;
	
	tree_copy_base(root->left, dest, size);
	dest[*size] = root->data;
	++ *size;
	tree_copy_base(root->right, dest, size);
}

void tree_copy(const TREE* tree, int* dest, int* size)
{
	*size = 0;
	tree_copy_base(*tree, dest, size);
}

void tree_clear_base(TREE_NODE* root)
{
	if (!root)
		return;
	
	tree_clear_base(root->left);
	tree_clear_base(root->right);
	free(root);
}

void tree_clear(TREE* tree)
{
	tree_clear_base(*tree);
	*tree = NULL;
}

size_t bin_find(int* array, size_t size, const int x)
{
	if (!size)
		return 0;
	
	size_t head = 0;
	size_t tail = size - 1;
	size_t mid;

	while (1)
	{
		mid = (head + tail) / 2;
		
		if (array[mid] < x)
			head = mid + 1;
		else if (x < array[mid])
			tail = mid;
		else
			return mid;
	}

	return size;
}

int main(void)
{
	int array[ARR_SIZE];
	int input, size;
	TREE tree;

	tree_init(&tree);

	for (int i = 0; i < ARR_SIZE; ++i)
	{
		scanf("%d", &input);
		tree_insert(&tree, input);
	}

	tree_copy(&tree, array, &size);
	for (int i = 0; i < size; ++i)
	{
		printf("%3d", array[i]);
	}
	putchar('\n');

	int index = bin_find(array, size, 21);
	printf("%d", index);

	tree_clear(&tree);

	return 0;
}