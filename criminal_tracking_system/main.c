#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

/**
 * main - Entry point for the program
 * Represents a network of people connected (friendships) as a graph.
 * Allows the user to choose a "criminal" and perform a BFS traversal to
 * categorize the people connected to the criminal in levels.
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
    graph_t *network = create_network();
    char criminal_name[100];
    vertex_t *criminal;

    if (!network)
    {
        printf("Error: Could not create the network.\n");
        return 1;
    }

    if (!build_network(network))
    {
        printf("Error: Failed to build the network.\n");
        network_delete(network);
        return 1;
    }

    printf("Enter the name of the criminal (case-sensitive): ");
    if (!fgets(criminal_name, sizeof(criminal_name), stdin))
    {
        printf("Error: Invalid input.\n");
        network_delete(network);
        return 1;
    }

    criminal_name[strcspn(criminal_name, "\n")] = '\0';

    criminal = search_member(network, criminal_name);
    if (!criminal)
    {
        printf("Error: %s is not in the network.\n", criminal_name);
        network_delete(network);
        return 1;
    }

    printf("Performing BFS traversal starting from %s...\n\n", criminal_name);
    if (!bfs_traverse(network, criminal))
    {
        printf("Error: BFS traversal failed.\n");
        network_delete(network);
        return 1;
    }

    network_delete(network);
    return 0;
}
