#include "graph.h"

#include <time.h>

#define NUM_VERTICES 20
#define NUM_EDGES 15
#define MAX_WEIGHT 100

/**
 * build_dijkstra_graph - creates a new graph with 20 vertices and 15 edges with random weights
 * Return: pointer to the graph
 */
graph_t *build_dijkstra_graph(void)
{
    graph_t *graph;
    vertex_t *vertex;
    size_t i, src, dest;
    int weight;

    /* Seed random number generator */
    srand(time(NULL));

    graph = graph_create();
    if (!graph)
        return NULL;

    /* Add 20 vertices to the graph */
    for (i = 0; i < NUM_VERTICES; i++)
    {
        vertex = add_vertex(graph);
        if (!vertex)
        {
            graph_delete(graph);
            return NULL;
        }
    }

    /* Add 15 random unidirectional edges between vertices with random weights */
    for (i = 0; i < NUM_EDGES; i++)
    {
        /* Randomly pick two different vertices */
        src = rand() % NUM_VERTICES;
        dest = rand() % NUM_VERTICES;
        while (dest == src)
        {
            dest = rand() % NUM_VERTICES;
        }

        /* Generate a random weight between 1 and MAX_WEIGHT */
        weight = (rand() % MAX_WEIGHT) + 1;

        if (!add_edge(graph, src, dest, weight))
        {
            printf("Failed to add edge between vertex %zu and vertex %zu\n", src, dest);
        }
    }

    return graph;
}
