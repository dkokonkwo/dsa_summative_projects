#include "graph.h"

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
 * dijkstra_traversal - traverses through graph
 * @priority_queue: priority queue
 * @predecessor: array of predecessor
 * @start: current vertex / beginning vertex
 */
void dijkstra_traversal(heap_t *priority_queue, int predecessor[], vertex_t *start)
{
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
    dijkstra_traversal(priority_queue, predecessor, dequeue(priority_queue));
}
