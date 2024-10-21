#ifndef GRAPH_H
#define GRAPH_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct vertex_s vertex_t;

/**
 * struct edge_t - edge connecting a node
 * @dest: pointer to the connected vertex
 * @next: pointer to next edge
 */
typedef struct edge_s
{
    vertex_t *dest;
    struct edge_s *next;
} edge_t;

/**
 * struct vertex_t - vertex in graph
 * @index: index of vertex in adjacency list
 * @name: connection name
 * @nb_edges: number of connections
 * @first: pointer to first connection
 * @next: pointer to the next vertex in adjacency list
 */
typedef struct vertex_s
{
    size_t index;
    char *name;
    size_t nb_edges;
    edge_t *first;
    struct vertex_s *next;
} vertex_t;

/**
 * struct graph_s - representation of a social network as a graph
 * @nb_vertices: number of vertices in social network
 * @head: first vertex in adjacency linked list
 */
typedef struct graph_s
{
    size_t nb_vertices;
    vertex_t *head;
} graph_t;

typedef struct node_s
{
    vertex_t *vertex;
    struct node_s *next;
} node_t;

typedef struct queue_s
{
    size_t nb_nodes;
    node_t *head;
    node_t *tail
} queue_t;

/* queue_functions.c  */
queue_t *create_queue(void);
void enqueue(queue_t *q, vertex_t *v);
vertex_t *dequeue(queue_t *q);

/* cts_functions.c */
graph_t *create_network(void);
vertex_t *add_member(graph_t *network, char *name);
vertex_t *search_member(graph_t *network, char *name);
int create_connection(graph_t *network, char *src, char *dest);
int bfs_traverse(graph_t *network, vertex_t *criminal);
void network_delete(graph_t *network);

#endif
