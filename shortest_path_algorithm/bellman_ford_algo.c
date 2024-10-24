#include "graph.h"

/**
 * bellman_ford_traversal - traverses all edges in graph
 * @graph: pointer to graph for traversing
 * @predecessor: array of predecessors
 * Return: number or relaxed values
 */
int bellman_ford_traversal(graph_t *graph, size_t *predecessor)
{
    int update;
    vertex_t *current_vertex;
    edge_t *edge;
    if (!graph)
        return 0;
    update = 0;
    for (current_vertex = graph->head; current_vertex; current_vertex = current_vertex->next)
    {
        for (edge = current_vertex->edges; edge; edge = edge->next)
        {
            if (edge->dest->value > (current_vertex->value + edge->weight))
            {
                edge->dest->value = current_vertex->value + edge->weight;
                predecessor[edge->dest->index] = current_vertex->index;
                update++;
            }
        }
    }
    return update;
}

/**
 * bellman_ford_graph - find shortest path using traversal
 * @graph: pointer to graph
 * Return: 1 on sucess else 0 on failure
 */
int bellman_ford_graph(graph_t *graph)
{
    size_t *predecessor, i;
    int has_update;
    if (!graph || graph->nb_vertices == 0)
        return 0;
    size_t sweep = 0;
    predecessor = malloc(graph->nb_vertices * sizeof(size_t));
    if (!predecessor)
        return 0;
    for (i = 0; i < graph->nb_vertices; i++)
    {
        predecessor[i] = SIZE_MAX;
    }
    graph->head->value = 0;
    while (sweep <= graph->nb_vertices - 1)
    {
        has_update = bellman_ford_traversal(graph, predecessor);
        if (!has_update)
        {
            printf("No update\n");
            break;
        }
        else
        {
            printf("Has update\n");
            sweep++;
        }
    }
    if (sweep > 0 && sweep <= graph->nb_vertices - 1)
    {
        printf("Shortest paths:\n");
        for (i = 0; i < graph->nb_vertices; i++)
        {
            if (predecessor[i] != SIZE_MAX)
                trace_path(i, predecessor);
        }
    }
    else if (sweep >= graph->nb_vertices)
    {
        fprintf(stderr, "Graph contains a negative weight cycle.\n");
        free(predecessor);
        return 0;
    }
    free(predecessor);

    return 1;
}
