#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 64

typedef struct tree_node
{
	char data;
	struct tree_node *left;
	struct tree_node *right;
} TREE_NODE, *TREE;

typedef struct queue_node
{
	TREE_NODE *data;
	struct queue_node *next;
} QUEUE_NODE;

typedef struct
{
	QUEUE_NODE *head;
	QUEUE_NODE *tail;
} QUEUE;

void queue_init(QUEUE *queue)
{
	queue->head = queue->tail = NULL;
}

void queue_push(QUEUE *queue, TREE_NODE *const x)
{
	QUEUE_NODE *new_node = (QUEUE_NODE *)malloc(sizeof(QUEUE_NODE));
	if (!new_node)
	{
		fprintf(stderr, "no memory\n");
		exit(EXIT_FAILURE);
	}
	new_node->data = x;
	new_node->next = NULL;

	if (!queue->tail)
	{
		queue->head = queue->tail = new_node;
	}
	else
	{
		queue->tail->next = new_node;
		queue->tail = new_node;
	}
}

_Bool queue_pop(QUEUE *queue, TREE_NODE **x)
{
	if (!queue->head)
		return 0;

	QUEUE_NODE *to_del = queue->head;

	queue->head = to_del->next;
	*x = to_del->data;

	if (to_del == queue->tail)
		queue->tail = NULL;

	free(to_del);

	return 1;
}

_Bool queue_empty(const QUEUE *queue)
{
	return !queue->head;
}

void queue_clear(QUEUE* queue)
{
	QUEUE_NODE* cur = queue->head;
	QUEUE_NODE* to_del;

	while (cur)
	{
		to_del = cur;
		cur = cur->next;
		free(to_del);
	}

	queue->head = queue->tail = NULL;
}

TREE_NODE *create_tree_node(char x)
{
	TREE_NODE *new_node = (TREE_NODE *)malloc(sizeof(TREE_NODE));
	if (!new_node)
	{
		fprintf(stderr, "no memory\n");
		exit(EXIT_FAILURE);
	}
	new_node->data = x;
	new_node->left = new_node->right = NULL;
	return new_node;
}

void create_tree_by_str(TREE *tree, const char *msg)
{
	const char *ch = msg;
	QUEUE queue;

	TREE_NODE *new_tree = NULL;
	TREE_NODE *tmp;
	TREE_NODE *cur = NULL;

	queue_init(&queue);

	while (*ch)
	{
		tmp = create_tree_node(*ch++);
		if (!cur)
		{
			cur = tmp;
			new_tree = cur;
		}
		else
		{
			queue_push(&queue, tmp);
			if (!cur->left)
			{
				cur->left = tmp;
			}
			else // if (!cur->right)
			{
				cur->right = tmp;
				queue_pop(&queue, &cur);
			}
		}
	}
	*tree = new_tree;

	queue_clear(&queue);
}

void print_tree(const TREE* tree)
{
	if (! *tree)
		return;
	
	putchar((*tree)->data);

	print_tree(& (*tree)->left);
	print_tree(& (*tree)->right);
}

void tree_clear_base(TREE_NODE* node)
{
	if (!node)
		return;
	
	tree_clear_base(node->left);
	tree_clear_base(node->right);
	free(node);
}

void tree_clear(TREE* tree)
{
	tree_clear_base(*tree);
	*tree = NULL;
}

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
	char buff[BUFF_SIZE];
	TREE tree;

	get_line(buff, BUFF_SIZE);

	create_tree_by_str(&tree, buff);

	print_tree(&tree);

	tree_clear(&tree);

	return 0;
}