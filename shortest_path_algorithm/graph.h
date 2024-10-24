#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>

typedef struct vertex_s vertex_t;

/**
 * struct edge_s - structure for edges in a graph
 * @dest: pointer to destination vertex
 * @weight: weight of the graph
 * @next: pointer to next edge in adjacency list
 */
typedef struct edge_s
{
    vertex_t *dest;
    int weight;
    struct edge_s *next;
} edge_t;

/**
 * struct vertex_s - verterx strucuture for graph
 * @index: vertex positon in graph
 * @value: integer value inherent to a vertex
 * @nb_edges: number of edges the connected vertex
 * @edges: pointer to first edge in adjecency list
 * @next: pointer to next vertex in adjacency list
 */
typedef struct vertex_s
{
    size_t index;
    int value;
    size_t nb_edges;
    edge_t *edges;
    struct vertex_s *next;
} vertex_t;


/**
 * struct graph_s - graph structure
 * @nb_vertices: number of vertices in graph
 * @head: pointer to head of the graph
 */
typedef struct graph_s
{
    size_t nb_vertices;
    vertex_t *head;
    vertex_t *tail;
} graph_t;

/*MIN HEAP STRUCTURE*/
/**
 * struct heap_t - heap structure for priority queue
 * @heapArr: resizing array for storing vertices
 * @size: size of heapArr
 * @nb_vertices: number of vertices in array
 */
typedef struct heap_s
{
    vertex_t **heapArr;
    size_t size;
    size_t nb_vertices;
} heap_t;

/* heap functions */
heap_t *heap_create(void);
void swap(heap_t *heap, int p1, int p2);
vertex_t *dequeue(heap_t *heap);
void sift_down(heap_t *heap);
void enqueue(heap_t *heap, vertex_t *vertex);
void sift_up(heap_t *heap, size_t position);
void print_queue(heap_t *q);
void heap_sort(heap_t *heap);

/* graph functions */
int add_edge(graph_t *graph, size_t src, size_t dest, int weight);
int is_connected(vertex_t *src, vertex_t *dest);
void graph_delete(graph_t *graph);
vertex_t *add_vertex(graph_t *graph);
graph_t *graph_create(void);
void trace_path(size_t target, size_t *predecessor);

/* Dijkstra's algorithm functions */
void dijkstra_traversal(heap_t *priority_queue, size_t *predecessor, int *visited, vertex_t *start);
int dijkstra_graph(graph_t *graph);

/* Bellman-Ford's algorithm functions */
int bellman_ford_traversal(graph_t *graph, size_t *predecessor);
int bellman_ford_graph(graph_t *graph);

/* build graphs */
graph_t *build_dijkstra_graph(void);
graph_t *build_bellman_ford_graph(void);

#endif