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


/**
 * build_bellman_ford_graph - creates a new graph for testing Bellman-Ford algorithm
 * Return: pointer to graph or NULL on failure
 */
graph_t *build_bellman_ford_graph(void)
{
    graph_t *graph = graph_create(); // Create a new graph
    if (!graph)
        return NULL;

    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < 20; i++)
    {
        if (!add_vertex(graph))
        {
            graph_delete(graph);
            return NULL;
        }
    }

    // Add edges with random weights, some of which are negative
    for (size_t i = 0; i < 20; i++)
    {
        for (size_t j = 0; j < 20; j++)
        {
            if (i != j)
            {
                int weight = rand() % 20;
                // Randomly decide if this edge should be negative
                if (rand() % 10 < 3) // 30% chance of being negative
                {
                    weight = -weight;
                }

                if (!add_edge(graph, i, j, weight)) 
                {
                    graph_delete(graph);
                    return NULL;
                }
            }
        }
    }

    return graph;
}

