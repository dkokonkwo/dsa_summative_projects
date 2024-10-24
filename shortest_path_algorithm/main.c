#include "graph.h"

// create options to run either dijkstra's or bellma-ford's algorithm
// for dijkstra build a dikstra graph and find the shortest path for all node
// for b-f build a be

/**
 * display_menu - menu for finding the shortest path
 */
void display_menu(void)
{
    printf("Find the Shortest Path.\n");
    printf("To test either algorithm.\n");
    printf("Type 1 find the shortest path using Dijkstra's algorithm.\n");
    printf("Type 2 to find the shortest path using the updated Bellman-Ford algorithm.\n");
    printf("Type 3 to exit the program.\n");
}

/**
 * main - tests both alogirithms for finding shortest path
 * Return: 0 on suceess else 1 on failure
 */
int main (void)
{
    int status;
    graph_t *graph;
    heap_t *priority_queue;
    int predecessors[];
    display_menu();
    scanf("%d", status);
    while (1)
    {
        switch (status)
        {
        case 1:
            graph = build_dijkstra_graph();
            if (!)
            break;

        default:
            break;
        }
    }

}