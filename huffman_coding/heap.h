#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

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
    int nb_nodes;
    int (*data_cmp)(void *, void *);
    node_t **heapArr;
} heap_t;

symbol_t *create_symbol(char s, int freq);
node_t *create_node(node_t *parent, void *data);
heap_t *create_heap(int (*data_cmp)(void *, void *), int size);
int freq_cmp(void *a, void *b);

void swap(heap_t *heap, int a, int b);
void sift_down(heap_t *heap);
void *heap_extract(heap_t *heap);
void sift_up(heap_t *heap);
node_t *heap_insert(heap_t *heap, void *data);
node_t *extract_and_insert(heap_t *heap);
void tree_delete(node_t *node, void (*free_data)(void *));
void heap_delete(heap_t *heap, void (*free_data)(void *));

heap_t *create_priority_queue(char *sym_arr, int *freq_arr, int size);
heap_t *build_huffman_tree(char *sym_arr, int *freq_arr, int size);
void free_nested(void *data);
void print_tree(node_t *root);
void huffman_code(node_t *root, char *code, int level);

#endif
