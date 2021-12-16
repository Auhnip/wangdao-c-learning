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
		printf("%3d", cur->data);
		cur = cur->next;
	}
	putchar('\n');
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

_Bool list_get(const LIST* list, int index, int* x)
{
	NODE* cur = list->head;
	for (int i = 0; i < index && cur; ++i, cur = cur->next)
		continue;
	
	if (!cur)
		return 0;
	
	*x = cur->data;

	return 1;
}

_Bool list_insert(LIST* list, int index, int x)
{
	static NODE tmp;
	tmp.next = list->head;

	NODE* prev = &tmp;
	for (int i = 0; prev && i < index; ++i, prev = prev->next)
		continue;
	
	if (!prev)
		return 0;
	
	NODE* new_node = create_node(x);
	new_node->next = prev->next;
	prev->next = new_node;

	if (list->tail == prev)
		list->tail = new_node;
	
	return 1;
}

_Bool list_remove(LIST* list, int index)
{
	static NODE tmp;
	tmp.next = list->head;

	NODE* prev = &tmp;
	for (int i = 0; prev && i < index; ++i, prev = prev->next)
		continue;
	
	if (!prev || !prev->next)
		return 0;
	
	if (list->tail == prev->next)
		list->tail = prev;
	
	NODE* to_del = prev->next;
	prev->next = to_del->next;
	free(to_del);

	return 1;
}

int main(void)
{
	LIST list;
	int input;

	list_init(&list);

	while (~scanf("%d", &input) && input != 9999)
		list_push_back(&list, input);
	
	list_get(&list, 1, &input);
	printf("%d\n", input);

	list_insert(&list, 1, 99);
	list_print(&list);

	list_remove(&list, 3);
	list_print(&list);

	list_clear(&list);

	return 0;
}