#include "graph.h"


/**
 * dijkstra_traversal - traverses through graph
 * @priority_queue: priority queue
 * @predecessor: array of predecessor
 * @visited: keeps track of visited vertices
 * @start: current vertex / beginning vertex
 */
void dijkstra_traversal(heap_t *priority_queue, size_t *predecessor, int *visited, vertex_t *start)
{
    vertex_t *next;
    edge_t *edge;
    int in_heap;
    if (!start)
        return;
    visited[start->index] = 1;
    if (start->nb_edges)
    {
        for (edge = start->edges; edge; edge = edge->next)
        {
            in_heap = edge->dest->value == INT_MAX ? 0 : 1;
            if (edge->dest->value > (start->value + edge->weight))
            {
                edge->dest->value = start->value + edge->weight;
                if (!visited[edge->dest->index])
                    predecessor[edge->dest->index] = start->index;
                if (!in_heap && !visited[edge->dest->index])
                {
                    enqueue(priority_queue, edge->dest);
                }
            }
        }
        heap_sort(priority_queue);
    }
    next = dequeue(priority_queue);
    if (next)
        dijkstra_traversal(priority_queue, predecessor, visited, next);
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
    int *visited = malloc(graph->nb_vertices * sizeof(int));
    if (!visited)
        return 0;
    size_t *predecessor = malloc(graph->nb_vertices * sizeof(size_t));
    if (!predecessor)
    {
        free(visited);
        return 0;
    }
    heap_t *priority_queue = heap_create();
    if (!priority_queue)
    {
        free(visited);
        free(predecessor);
        return 0;
    }
    for (i = 0; i < graph->nb_vertices; i++)
    {
        predecessor[i] = SIZE_MAX;
        visited[i] = 0;
    }
    graph->head->value = 0;

    dijkstra_traversal(priority_queue, predecessor, visited, graph->head);

    printf("Shortest paths: size: %lu\n", graph->nb_vertices);
    for (i = 0; i < graph->nb_vertices; i++)
    {
        if (predecessor[i] != SIZE_MAX)
        {
            trace_path(i, predecessor);
        }
    }
    free(priority_queue->heapArr);
    free(priority_queue);
    free(visited);
    free(predecessor);
    return 1;
}