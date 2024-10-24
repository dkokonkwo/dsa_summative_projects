#include "graph.h"

#include <time.h>

#define NUM_VERTICES 20
#define NUM_EDGES 15
#define MAX_WEIGHT 100

/**
 * build_dijkstra_graph - creates a new graph with 6 vertices and edges with postive weights
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
 * build_bellman_ford_graph - creates a new graph with 6 vertices and negatively weighte edges
 * Return: pointer to the graph
 */
graph_t *build_bellman_ford_graph(void)
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
    success &= add_edge(graph, 2, 4, -30);
    success &= add_edge(graph, 3, 5, 20);
    success &= add_edge(graph, 4, 5, 25);
    success &= add_edge(graph, 4, 3, 45);
    if (!success)
        printf("adding edges went wrong.\n");
    else
        printf("Created graph with %lu vertices\n", graph->nb_vertices);
    return graph;
}

