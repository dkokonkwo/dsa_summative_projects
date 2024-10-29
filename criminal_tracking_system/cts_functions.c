#include "graph.h"

/**
 * create_network - create a new network as graph
 * Return: pointer to new network on success else NULL
 */
graph_t *create_network(void)
{
    graph_t *new_network = (graph_t *)malloc(sizeof(graph_t));
    if (!new_network)
        return NULL;
    new_network->head = NULL;
    new_network->nb_vertices = 0;
    return new_network;
}

/**
 * add_member - add a new member to network
 * @network: graph to add member to
 * @name: member name
 * Return: new member on success else NULL
 */
vertex_t *add_member(graph_t *network, char *name)
{
    if (!network || !name)
        return NULL;
    vertex_t *new_member = (vertex_t *)malloc(sizeof(vertex_t));
    if (!new_member)
        return NULL;
    new_member->name = strdup(name);
    if (!new_member->name)
    {
        free(new_member);
        return NULL;
    }
    new_member->first = NULL;
    new_member->nb_edges = 0;
    new_member->next = NULL;
    new_member->index = network->nb_vertices++;
    if (!network->head)
        network->head = new_member;
    else
    {
        vertex_t *current;
        for (current = network->head; current->next; current = current->next)
        {
            ;
        }
        current->next = new_member;
    }
    return new_member;
}

/**
 * search_member - find vertex that matches with name
 * @network: graph with vertices
 * @name: member name
 * Return: pointer to member vertex if found else NULL
 */
vertex_t *search_member(graph_t *network, char *name)
{
    vertex_t *curr;
    if (!network || !name)
        return NULL;
    for (curr = network->head; curr; curr = curr->next)
    {
        if (strcasecmp(curr->name, name) == 0)
            return curr;
    }
    return NULL;
}

/**
 * create_connection - adds edges between two members
 * @network: network to create connection in
 * @src: name of source member
 * @dest: name of destination member
 * Return: 1 on success, 0 on error
 */
int create_connection(graph_t *network, char *src, char *dest)
{
    vertex_t *src_v, *dest_v;
    edge_t *src_e, *dest_e, *curr_edge;
    if (!network || !src || !dest)
        return 0;
    src_v = search_member(network, src);
    dest_v = search_member(network, dest);
    if (!(src_v && dest_v))
        return 0;
    if (is_connected(src_v, dest_v))
    {
        printf("Already connected.\n");
        return 1;
    }
    src_e = (edge_t *)malloc(sizeof(edge_t));
    if (!src_e)
        return 0;
    dest_e = (edge_t *)malloc(sizeof(edge_t));
    if (!dest_e) 
        return 0;
    /*source to destination edge*/
    src_e->dest = dest_v, src_e->next = NULL;
    if (!src_v->first)
        src_v->first = src_e;
    else
    {
        for (curr_edge = src_v->first; curr_edge->next; curr_edge = curr_edge->next)
        {
            ;
        }
        curr_edge->next = src_e;
    }
    src_v->nb_edges++;
    /*destination to source edge*/
    dest_e->dest = src_v, dest_e->next = NULL;
    if (!dest_v->first)
        dest_v->first = dest_e;
    else
    {
        for (curr_edge = dest_v->first; curr_edge->next; curr_edge = curr_edge->next)
        {
            ;
        }
        curr_edge->next = dest_e;
    }
    dest_v->nb_edges++;
    return 1;
}

/**
 * is_connected - finds out if two members are connected
 * @src: first member
 * @dest: second member
 * Return: 1 if connected else 0
 */
int is_connected(vertex_t *src, vertex_t *dest)
{
    edge_t *curr;
    if (!src || !dest)
        return 0;
    for (curr = src->first; curr; curr = curr->next)
    {
        if (strcasecmp(curr->dest->name, dest->name) == 0)
            return 1;
    }
    return 0;
}

/**
 * bfs_traverse - find members connected to the criminal
 * @network: network of members
 * @criminal: criminal to search for network
 * Return: 1 on success else 0 on failure
 */
int bfs_traverse(graph_t *network, vertex_t *criminal)
{
    int *visited;
    size_t vertices_in_level, next_level_count, current_depth = 0;
    queue_t *queue;
    vertex_t *member;
    edge_t *edge;
    if (!network || !network->nb_vertices || !criminal)
        return 0;
    visited = calloc(network->nb_vertices, sizeof(int));
    if (!visited)
        return 0;
    queue = create_queue();
    enqueue(queue, criminal);
    visited[criminal->index] = 1;
    vertices_in_level = 1; next_level_count = 0;
    while (queue->nb_nodes)
    {
        member = dequeue(queue);
        if (current_depth == 0)
            printf("Prime Suspect: %s", member->name);
        else if (current_depth == 1)
            printf("Name: %s Category: Direct Contact\n", member->name);
        else
            printf("Name: %s Category: Level %lu\n", member->name, current_depth);
        for (edge = member->first; edge; edge = edge->next)
        {
            if (!visited[edge->dest->index])
            {
                enqueue(queue, edge->dest);
                visited[edge->dest->index] = 1;
                next_level_count++;
            }
        }
        vertices_in_level--;
        if (vertices_in_level == 0)
        {
            current_depth++;
            vertices_in_level = next_level_count;
            next_level_count = 0;
        }
    }
    return 1;
}

/**
 * network_delete - completely deletes a graph
 * @network: pointer to the graph to delete
 */
void network_delete(graph_t *network)
{
    vertex_t *vertex, *temp_vertex;
    edge_t *edge, *temp_edge;

    if (!network)
        return;
    vertex = network->head;
    while (vertex)
    {
        edge = vertex->first;
        while (edge)
        {
            temp_edge = edge->next;
            free(edge);
            edge = temp_edge;
        }

        if (vertex->name)
            free(vertex->name);

        temp_vertex = vertex->next;
        free(vertex);
        vertex = temp_vertex;
    }

    free(network);
}

int build_network(graph_t *network)
{
    int i, conn;
    vertex_t *new_member;
    char *members[] =
    {
        "Alice Bennett",
        "Marcus Carter",
        "Isabella Diaz",
        "Henry Foster",
        "Chloe Grant",
        "Benjamin Hayes",
        "Olivia Jenkins",
        "Daniel King",
        "Emily Lewis",
        "Jack Miller",
        "Mia Parker",
        "Ethan Roberts",
        "Sophie Turner",
        "Lucas White",
        "Grace Young"
    };
    for (i = 0; i < 15; i++)
    {
        new_member = add_member(network, members[i]);
        if (!new_member)
        {
            network_delete(network);
            return 0;
        }
        printf("Adding %s to network...\n", members[i]);
    }
    conn = create_connection(network, members[0], members[1]);
    conn &= create_connection(network, members[0], members[2]);
    conn &= create_connection(network, members[1], members[7]);
    conn &= create_connection(network, members[5], members[12]);
    conn &= create_connection(network, members[12], members[8]);
    conn &= create_connection(network, members[10], members[14]);
    conn &= create_connection(network, members[3], members[14]);
    conn &= create_connection(network, members[4], members[5]);
    conn &= create_connection(network, members[8], members[0]);
    conn &= create_connection(network, members[3], members[7]);
    if (!conn)
    {
        printf("Error: failed to create some connections.");
        network_delete(network);
        return 0;
    }
    return 1;
}
