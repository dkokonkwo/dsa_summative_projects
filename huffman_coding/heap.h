#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * struct symbol_s - symbol structure
 * @symbol: symbol in structure
 * @freq: frequency of symbol
 */
typedef struct symbol_s
{
    char data;
    int freq;
} symbol_t;

/**
 * struct node_s - struct for a heap node
 * @data: symbol from text file
 * @freq: frequency of symbol
 * @left: left child of node
 * @right: right child of node
 */
typedef struct node_s
{
    void *data;
    struct node_s *parent;
    struct node_s *left;
    struct node_s *right;
} node_t;

/**
 * struct heap_s - heap structure
 * @nb_nodes: number of nodes in heap
 * @data_cmp: function for comparing two frequencies
 * @root: top node in heap
 */
typedef struct heap_s
{
    int size;
    int (*data_cmp)(void *, void *);
    node_t **heapArr;
} heap_t;

symbol_t *create_symbol(char *s, int freq);
node_t *create_node(node_t *parent, void *data);
heap_t *create_heap(int (*data_cmp)(void *, void *), int size);
int freq_cmp(void *a, void *b);

void swap(void *a, void *b);
void sift_down(heap_t *heap);
void *heap_extract(heap_t *heap);
void sift_up(heap_t *heap);
node_t *heap_insert(heap_t *heap, void *data);
node_t *extract_and_insert(heap_t *heap);

#endif
