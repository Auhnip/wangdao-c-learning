#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
} NODE;

typedef struct list
{
	NODE* head;
	NODE* tail;
} LIST;

void list_init(LIST* list)
{
	list->head = list->tail = NULL;
}

NODE* create_node(int x)
{
	NODE* ret = (NODE*)malloc(sizeof(NODE));
	if (!ret)
	{
		fprintf(stderr, "bad alloc\n");
		exit(EXIT_FAILURE);
	}
	ret->data = x;
	ret->next = NULL;
	return ret;
}

_Bool list_empty(LIST* list)
{
	return list->head == NULL;
}

void list_push_front(LIST* list, int x)
{
	NODE* new_node = create_node(x);

	if (list->head == NULL)
	{
		list->head = list->tail = new_node;
	}
	else
	{
		new_node->next = list->head;
		list->head = new_node;
	}
}

void list_push_back(LIST* list, int x)
{
	NODE* new_node = create_node(x);
	if (list->tail == NULL)
	{
		list->head = list->tail = new_node;
	}
	else
	{
		list->tail->next = new_node;
		list->tail = new_node;
	}
}

void list_print(const LIST* list)
{
	NODE* cur = list->head;

	while (cur)
	{
		printf("%d", cur->data);
		putchar(cur->next ? ' ' : '\n');

		cur = cur->next;
	}
}

void list_clear(LIST* list)
{
	NODE* cur = list->head;
	NODE* to_del;

	while (cur)
	{
		to_del = cur;
		cur = cur->next;
		free(to_del);
	}
	list->head = list->tail = NULL;
}

int main(void)
{
	LIST list1, list2;
	int input;

	list_init(&list1);
	list_init(&list2);

	while (~scanf("%d", &input) && input != 9999)
	{
		list_push_front(&list1, input);
	}
	list_print(&list1);

	while (~scanf("%d", &input) && input != 9999)
	{
		list_push_back(&list2, input);
	}
	list_print(&list2);

	list_clear(&list1);
	list_clear(&list2);

	return 0;
}