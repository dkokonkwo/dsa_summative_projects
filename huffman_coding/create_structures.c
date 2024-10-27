#include "heap.h"

/**
 * create_heap - create heap structure
 * @data_cmp: function for comparing symbol frequencies
 * @size: size of heap
 * Return: pointer to new heap else NULL
 */
heap_t *create_heap(int (*data_cmp)(void *, void *), int size)
{
    node_t **heapArr;
    if (!data_cmp)
        return NULL;
    heap_t *minHeap = (heap_t *)malloc(sizeof(heap_t));
    if (!minHeap)
        return NULL;
    heapArr = (node_t **)malloc((size + 1) * sizeof(node_t *));
    if (!heapArr)
    {
        free(minHeap);
        return NULL;
    }
    minHeap->nb_nodes = 0;
    minHeap->size = size + 1;
    minHeap->data_cmp = data_cmp;
    minHeap->heapArr = heapArr;
    return minHeap;
}

/**
 * create_node - creates new node
 * @parent: parent node
 * @data: symbol structure
 * Return: pointer to new node else NULL
 */
node_t *create_node(node_t *parent, void *data)
{
    if (!data)
        return NULL;
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (!new_node)
        return NULL;
    new_node->data = data;
    new_node->parent = parent;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/**
 * create_symbol - creates new symbol structure
 * @s: symbol character
 * @freq: symbol frequency
 * Return: pointer to symbol or NULL on failure
 */
symbol_t *create_symbol(char s, int freq)
{
    if (!s || freq < 1)
        return NULL;
    symbol_t *symbol = (symbol_t *)malloc(sizeof(symbol_t));
    if (!symbol)
        return NULL;
    symbol->data = s;
    symbol->freq = freq;
    return symbol;
}

/**
 * freq_cmp - compares frquencies of two symbols
 * @a: symbol a
 * @b: symbol b
 * Return: comparison between the value
 */
int freq_cmp(void *a, void *b)
{
    node_t *n1, *n2;
    int f1, f2;
    n1 = (node_t *) a;
    n2 = (node_t *) b;
    f1 = ((symbol_t *)n1->data)->freq;
    f2 = ((symbol_t *)n2->data)->freq;
    return f1 - f2;
}