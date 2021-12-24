#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int* content;
	unsigned top;
	unsigned size;
} STACK;

typedef struct
{
	int * content;
	unsigned head;
	unsigned tail;
	unsigned size;
} QUEUE;

void stack_init(STACK* stack, unsigned size)
{
	stack->content = (int*)malloc(sizeof(int) * size);
	if (!stack->content)
	{
		fprintf(stderr, "bad alloc\n");
		exit(EXIT_FAILURE);
	}
	stack->top = 0;
	stack->size = size;
}

_Bool stack_empty(const STACK* stack)
{
	return ! stack->top;
}

_Bool stack_push(STACK* stack, int x)
{
	if (stack->top == stack->size)
		return 0;
	
	stack->content[stack->top++] = x;
	return 1;
}

_Bool stack_pop(STACK* stack, int* x)
{
	if (!stack->top)
		return 0;
	
	*x = stack->content[-- stack->top];
	return 1;
}

void stack_destroy(STACK* stack)
{
	free(stack->content);
}

void queue_init(QUEUE* queue, unsigned size)
{
	queue->content = (int*)malloc(sizeof(int) * size);
	if (!queue->content)
	{
		fprintf(stderr, "bad alloc\n");
		exit(EXIT_FAILURE);
	}
	queue->head = queue->tail = 0;
	queue->size = size;
}

_Bool queue_empty(const QUEUE* queue)
{
	return queue->head == queue->tail;
}

_Bool queue_full(const QUEUE* queue)
{
	return (queue->head + 1) % queue->size == queue->tail;
}

_Bool queue_push(QUEUE* queue, int x)
{
	unsigned new_tail = (queue->tail + 1) % queue->size;
	if (new_tail == queue->head)
		return 0;
	
	queue->content[queue->tail] = x;
	queue->tail = new_tail;
	return 1;
}

_Bool queue_pop(QUEUE* queue, int* x)
{
	if (queue->head == queue->tail)
		return 0;
	
	unsigned new_head = (queue->head + 1) % queue->size;

	*x = queue->content[queue->head];
	queue->head = new_head;

	return 1;
}

void queue_destroy(QUEUE* queue)
{
	free(queue->content);
}

int main(void)
{
	int input;
	STACK stack;
	QUEUE queue;

	stack_init(&stack, 3);
	queue_init(&queue, 5);

	for (int i = 0; i < 3; ++i)
	{
		scanf("%d", &input);
		stack_push(&stack, input);
	}

	while (!stack_empty(&stack))
	{
		stack_pop(&stack, &input);
		printf("%2d", input);
	}
	putchar('\n');

	while (~scanf("%d", &input) && queue_push(&queue, input))
		continue;
	
	printf("false\n");
	while (!queue_empty(&queue))
	{
		queue_pop(&queue, &input);
		printf("%2d", input);
	}
	putchar('\n');

	stack_destroy(&stack);
	queue_destroy(&queue);

	return 0;
}