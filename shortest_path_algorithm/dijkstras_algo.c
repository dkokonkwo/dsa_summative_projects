#include "graph.h"

#define MAX_SIZE 50

// create graph, add vertices to graph, connect vertices, 
/**
 * graph_create - create new graph
 * Return: pointer to graph else NULL on failure
 */
graph_t *graph_create(void)
{
    graph_t *graph = (graph_t *)malloc(sizeof(graph_t));
    if (!graph)
        return NULL;
    graph->head = NULL;
    graph->tail = NULL;
    graph->nb_vertices = 0;
    return graph;
}

/**
 * add_vertex - add vertex to graph
 * @graph: pointer to graph to add vertex
 * Return: pointer to vertex or NULL on failure
 */
vertex_t *add_vertex(graph_t *graph)
{
    vertex_t *vertex;
    if (!graph)
        return NULL;
    vertex = (vertex_t *)malloc(sizeof(vertex_t));
    if (!vertex)
        return NULL;
    vertex->edges = NULL;
    vertex->nb_edges = 0;
    vertex->next = NULL;
    vertex->value = INT_MAX;
    if (graph->nb_vertices == 0)
    {
        graph->head = vertex;
        graph->tail = vertex;
    }
    else
    {
        graph->tail->next = vertex;
        graph->tail = vertex;
    }
    vertex->index = graph->nb_vertices++;
    return vertex;
}

/**
 * is_connected - finds out if two vertices are connected
 * @src: first vertex
 * @dest: second vertex
 * Return: 1 if connected, 0 if not connected, -1 if valid input
 */
int is_connected(vertex_t *src, vertex_t *dest)
{
    edge_t *curr;
    if (!src || !dest)
        return -1;
    for (curr = src->edges; curr; curr = curr->next)
    {
        if (curr->dest == dest)
            return 1;
    }
    return 0;
}

/**
 * find_vertex - find vertex in graph that matches with index
 * @graph: pointer to graph
 * @index: vertex index
 * Return: pointer to member vertex if found else NULL
 */
vertex_t *find_vertex(graph_t *graph, size_t index)
{
    vertex_t *curr;
    if (!graph)
        return NULL;
    for (curr = graph->head; curr; curr = curr->next)
    {
        if (curr->index == index)
            return curr;
    }
    return NULL;
}

/**
 * add_edge - creates connection between to vertices
 * @graph: pointer to graph
 * @src: source vertex index 
 * @dest: destination vertex index
 * @weight: edge weight
 * Return: 1 on sucess else 0 on failure
 */
int add_edge(graph_t *graph, size_t src, size_t dest, int weight)
{
    vertex_t *src_v, *dest_v;
    edge_t *edge, *curr_edge;
    if (!graph)
        return 0;
    src_v = find_vertex(graph, src);
    dest_v = find_vertex(graph, dest);
    if (!(src_v && dest_v))
        return 0;
    if (is_connected(src_v, dest_v) == 1)
    {
        printf("Vertices are already connected.\n");
        return 1;
    }
    edge = (edge_t *)malloc(sizeof(edge_t));
    if (!edge)
        return 0;
    /*source to destination edge*/
    edge->dest = dest_v;
    edge->next = NULL;
    edge->weight = weight;
    if (!src_v->edges)
        src_v->edges = edge;
    else
    {
        for (curr_edge = src_v->edges; curr_edge->next; curr_edge = curr_edge->next)
        {
            ;
        }
        curr_edge->next = edge;
    }
    src_v->nb_edges++;
    return 1;
}

/**
 * dijkstra_traversal - traverses through graph
 * @priority_queue: priority queue
 * @predecessor: array of predecessor
 * @start: current vertex / beginning vertex
 */
void dijkstra_traversal(heap_t *priority_queue, int predecessor[], vertex_t *start)
{
    vertex_t *next;
    edge_t *edge;
    if (!start)
        return;
    if (start->nb_edges == 0)
        return;
    for (edge = start->edges; edge; edge = edge->next)
    {
        if (edge->dest->value > (start->value + edge->weight))
        {
            edge->dest->value = start->value + edge->weight;
            predecessor[edge->dest->index] = start->index;
            enqueue(priority_queue, edge->dest);
        }
    }
    next = dequeue(priority_queue);
    if (next)
        dijkstra_traversal(priority_queue, predecessor, next);
}

/**
 * trace_path - traces path between two points in a graph
 * @target: target vertex index
 * @predecessor: array of predecessors
 */
void trace_path(int target, int predecessor[])
{
    int path[MAX_SIZE];
    int count = 0;
    int i, current = target;
    while (predecessor[current] != -1)
    {
        path[count] = predecessor[current];
        current = predecessor[current];
        count++;
    }
    printf("%d", current);
    for (i = count - 1; i >= 0; i--)
    {
        printf(" --> %d", path[i]);
    }
    printf("\n");
}

/**
 * dijkstra_graph - perfom's algorithm on graph
 * @graph: pointer to graph
 * Return: 1 on success else 0 on failure
 */
int dijkstra_graph(graph_t *graph)
{
    size_t i;
    if (!graph || graph->nb_vertices == 0)
        return 0;
    heap_t *priority_queue = heap_create();
    int predecessor[graph->nb_vertices];
    for (i = 0; i < graph->nb_vertices; i++)
        predecessor[i] = -1;
    graph->head->value = 0;
    dijkstra_traversal(priority_queue, predecessor, graph->head);
    printf("Shortest paths:\n");
    for (i = 0; i < graph->nb_vertices; i++)
    {
        if (predecessor[i] != -1)
            trace_path(i, predecessor);
    }
    free(priority_queue->heapArr);
    free(priority_queue);

    return 1;
}

/**
 * graph_delete - delete vertices and graph
 * @graph: pointer to graph to delete
 */
void graph_delete(graph_t *graph)
{
    vertex_t *current_vertex, *next_vertex;
    edge_t *current_edge, *next_edge;
    if (graph)
    {
        current_vertex = graph->head;
        while (current_vertex)
        {
            current_edge = current_vertex->edges;
            while (current_edge)
            {
                next_edge = current_edge->next;
                free(current_edge);
                current_edge = next_edge;
            }

            next_vertex = current_vertex->next;
            free(current_vertex);
            current_vertex = next_vertex;
        }
        free(graph);
    }
}