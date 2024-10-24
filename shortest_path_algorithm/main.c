#include "graph.h"

// create options to run either dijkstra's or bellma-ford's algorithm
// for dijkstra build a dikstra graph and find the shortest path for all node

/**
 * display_menu - menu for finding the shortest path
 */
void display_menu(void)
{
    printf("Find the Shortest Path.\n");
    printf("1. Find the shortest path using Dijkstra's algorithm.\n");
    printf("2. Find the shortest path using the Bellman-Ford algorithm.\n");
    printf("3. Exit the program.\n");
}

/**
 * main - tests both alogirithms for finding shortest path
 * Return: 0 on suceess else 1 on failure
 */
int main (void)
{
    int status;
    graph_t *graph;

    while (1)
    {
        display_menu();
        printf("Enter your choice: ");
        if (scanf("%d", &status) != 1)
        {
            fprintf(stderr, "Invalid input. Exiting...\n");
            return 1;
        }

        while (getchar() != '\n');

        switch (status)
        {
        case 1:
            graph = build_dijkstra_graph();
            if (!graph)
            {
                fprintf(stderr, "Failed to build graph\n");
                break;
            }
            if (!dijkstra_graph(graph))
            {
                fprintf(stderr, "Failed to find shortest path.\n");
            }
            graph_delete(graph);
            break;
        case 2:
            graph = build_bellman_ford_graph();
            if (!graph)
            {
                fprintf(stderr, "Failed to build graph\n");
                break;
            }
            if (!bellman_ford_graph(graph))
            {
                fprintf(stderr, "Failed to find shortest path.\n");
            }
            graph_delete(graph);
            break;
        case 3:
            printf("Exiting program...\n");
            return 0;
        default:
            printf("Invalid choice. Please select a valid option.\n");
            break;
        }
    }
    return 1;
}