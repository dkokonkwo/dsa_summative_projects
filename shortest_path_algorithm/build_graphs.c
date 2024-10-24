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
    size_t i;
    int success;
    
    graph = graph_create();
    if (!graph)
        return NULL;
    
    // adding 6 vertices
    for (i = 0; i < 6; i++)
    {
        vertex = add_vertex(graph);
        if (!vertex)
        {
            graph_delete(graph);
            return NULL;
        }
    }
    
    // adding edges
    success = add_edge(graph, 0, 2, 35);
    success &= add_edge(graph, 0, 1, 5);
    success &= add_edge(graph, 0, 3, 40);
    success &= add_edge(graph, 1, 3, 20);
    success &= add_edge(graph, 1, 4, 25);
    success &= add_edge(graph, 2, 5, 30);
    success &= add_edge(graph, 2, 4, 30);
    success &= add_edge(graph, 3, 5, 20);
    success &= add_edge(graph, 4, 5, 25);
    success &= add_edge(graph, 4, 3, 45);
    if (!success)
        printf("adding edges went wrong.\n");
    else
        printf("Created graph with %lu vertices\n", graph->nb_vertices);
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

