#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vex_node
{
	unsigned end_index;
	struct vex_node *next;
} VEX_NODE;

typedef struct vex
{
	char name;
	VEX_NODE *first;
} VERTEX;

typedef struct graph
{
	unsigned vex_num;
	unsigned edge_num;
	VERTEX *vertices;
	unsigned vex_capacity;
} GRAPH;

void check_pointer(void *ptr, const char *msg)
{
	if (ptr)
		return;

	fprintf(stderr, msg);
	exit(EXIT_FAILURE);
}

GRAPH *graph_init()
{
	GRAPH *ret = (GRAPH *)malloc(sizeof(GRAPH));
	check_pointer(ret, "no memory\n");
	memset(ret, 0, sizeof(GRAPH));
	return ret;
}

static void adjust_space(GRAPH *g, unsigned space)
{
	if (g->vex_num + space <= g->vex_capacity)
		return;

	unsigned new_cap = g->vex_capacity;
	while (g->vex_num + space > new_cap)
		new_cap = (new_cap ? new_cap << 1 : 1);

	VERTEX *new_vetices = (VERTEX *)malloc(sizeof(VERTEX) * new_cap);
	check_pointer(new_vetices, "no memory\n");

	if (g->vertices)
	{
		memcpy(new_vetices, g->vertices, sizeof(VERTEX) * g->vex_num);
		free(g->vertices);
	}
	g->vertices = new_vetices;
	g->vex_capacity = new_cap;
}

void graph_add_vertex(GRAPH *graph, char name)
{
	adjust_space(graph, 1);
	graph->vertices[graph->vex_num].name = name;
	graph->vertices[graph->vex_num].first = NULL;
	++graph->vex_num;
}

static unsigned get_index(GRAPH *graph, char name)
{
	for (unsigned i = 0; i < graph->vex_num; ++i)
	{
		if (name == graph->vertices[i].name)
			return i;
	}
	return graph->vex_num;
}

static VEX_NODE *create_vex_node(unsigned index)
{
	VEX_NODE *ret = (VEX_NODE *)malloc(sizeof(VEX_NODE));
	check_pointer(ret, "no memory\n");

	ret->end_index = index;
	ret->next = NULL;

	return ret;
}

static VEX_NODE *add_to_tail(VEX_NODE *vlist, VEX_NODE *new_node)
{
	if (!vlist)
		return new_node;

	VEX_NODE *cur = vlist;
	while (cur->next)
		cur = cur->next;
	cur->next = new_node;

	return vlist;
}

_Bool graph_add_edge(GRAPH *graph, char begin, char end)
{
	unsigned begin_index = get_index(graph, begin);
	if (begin_index == graph->vex_num)
		return 0;

	unsigned end_index = get_index(graph, end);
	if (end_index == graph->vex_num)
		return 0;

	VEX_NODE *new_edge = create_vex_node(end_index);
	graph->vertices[begin_index].first = add_to_tail(graph->vertices[begin_index].first, new_edge);
	++graph->edge_num;

	return 1;
}

void graph_print_BFS(const GRAPH *graph)
{
	if (!graph->vex_num)
		return;

	int *reached = (int *)malloc(sizeof(int) * graph->vex_num);
	check_pointer(reached, "no memory\n");
	memset(reached, 0, sizeof(int) * graph->vex_num);

	unsigned *queue = (unsigned *)malloc(sizeof(unsigned) * graph->vex_num);
	check_pointer(queue, "no memory\n");

	unsigned head, tail, cur;

	for (unsigned i = 0; i < graph->vex_num; ++i)
	{
		if (reached[i])
			continue;

		head = tail = 0;
		queue[tail++] = i;
		reached[i] = 1;
		while (head != tail)
		{
			cur = queue[head++];
			for (VEX_NODE *edge = graph->vertices[cur].first; edge; edge = edge->next)
			{
				if (!reached[edge->end_index])
				{
					queue[tail++] = edge->end_index;
					reached[edge->end_index] = 1;
				}
			}
			printf("%2c", graph->vertices[cur].name);
		}
	}
	putchar('\n');

	free(reached);
	free(queue);
}

static void graph_print_DFS_base(const GRAPH *graph, unsigned index, int *reached)
{
	printf("%2c", graph->vertices[index].name);

	reached[index] = 1;
	for (VEX_NODE *edge = graph->vertices[index].first; edge; edge = edge->next)
	{
		if (!reached[edge->end_index])
			graph_print_DFS_base(graph, edge->end_index, reached);
	}
}

void graph_print_DFS(const GRAPH *graph)
{
	if (!graph->vex_num)
		return;

	int *reached = (int *)malloc(sizeof(int) * graph->vex_num);
	check_pointer(reached, "no memory\n");
	memset(reached, 0, sizeof(int) * graph->vex_num);

	for (unsigned i = 0; i < graph->vex_num; ++i)
	{
		if (!reached[i])
			graph_print_DFS_base(graph, i, reached);
	}
	putchar('\n');

	free(reached);
}

static void clear_list(VEX_NODE *list)
{
	VEX_NODE *to_del;
	while (list)
	{
		to_del = list;
		list = list->next;
		free(to_del);
	}
}

void graph_destroy(GRAPH *graph)
{
	for (unsigned i = 0; i < graph->vex_num; ++i)
		clear_list(graph->vertices[i].first);
	free(graph->vertices);
}

int main()
{
	char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	char edges[][2] = {
	    {'A', 'B'},
	    {'B', 'C'},
	    {'B', 'E'},
	    {'B', 'F'},
	    {'C', 'E'},
	    {'D', 'C'},
	    {'E', 'B'},
	    {'E', 'D'},
	    {'F', 'G'}};
	
	GRAPH* graph = graph_init();
	for (unsigned i = 0; i < sizeof(vexs) / sizeof(char); ++i)
		graph_add_vertex(graph, vexs[i]);

	for (unsigned i = 0; i < sizeof(edges) / sizeof(char); ++i)
		graph_add_edge(graph, edges[i][0], edges[i][1]);
	
	graph_print_DFS(graph);
	graph_print_BFS(graph);

	graph_destroy(graph);

	return 0;
}