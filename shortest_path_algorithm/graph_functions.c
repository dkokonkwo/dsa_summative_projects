#include "graph.h"

#define MAX_SIZE 50

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
 * trace_path - traces path between two points in a graph
 * @target: target vertex index
 * @predecessor: array of predecessors
 */
void trace_path(int target, size_t *predecessor)
{
    int path[MAX_SIZE];
    int count = 0;
    int i, current = target;
    while (predecessor[current] != SIZE_MAX)
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