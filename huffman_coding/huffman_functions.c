#include "heap.h"

/**
 * create_priority_queue - creates priority queue from symbols
 * @sym_arr: array of symbols
 * @freq_arr: array of corresponding frequencies
 * @size: size of both arrays
 * Return: priority queue heap or NULL on failure
 */
heap_t *create_priority_queue(char *sym_arr, int *freq_arr, int size)
{
    heap_t *priority_queue;
    symbol_t *symbol;
    node_t *node, *nested;
    int i;
    if (!sym_arr || !freq_arr || size < 1)
        return NULL;
    priority_queue = create_heap(freq_cmp, size);
    if (!priority_queue)
        return NULL;
    for (i = 0; i < size; i++)
    {
        symbol = create_symbol(sym_arr[i], freq_arr[i]);
        if (!symbol)
        {
            heap_delete(priority_queue, NULL);
            return NULL;
        }
        node = create_node(NULL, symbol);
        if (!node)
        {
            free(symbol);
            heap_delete(priority_queue, NULL);
            return NULL;
        }
        nested = heap_insert(priority_queue, node);
        if (!nested)
        {
            free(symbol);
            free(node);
            heap_delete(priority_queue, NULL);
            return NULL;
        }
    }
    return priority_queue;
}

/**
 * free_nested - free node and symbol structure
 * @data: pointer to be cast to node
 */
void free_nested(void *data)
{
    node_t *node_data;
    symbol_t *symbol_data;
    node_data = (node_t *)data;
    if (node_data)
    {
        symbol_data = (symbol_t *)node_data->data;
        if (symbol_data)
            free(symbol_data);
        free(node_data);
    }
}

/**
 * build_huffman_tree - build huffman tree from array of symbols
 * @sym_arr: array of symbols
 * @freq_arr: array of frequencies
 * @size: size of arrays
 * Return: pointer to root node of huffman tree or NULL on failure
 */
node_t *build_huffman_tree(char *sym_arr, int *freq_arr, int size)
{
    heap_t *priority_queue;
    node_t *huffman_root;
    if (!sym_arr || !freq_arr || size < 1)
        return NULL;
    priority_queue = create_priority_queue(sym_arr, freq_arr, size);
    if (!priority_queue)
        return NULL;
    while (priority_queue->size > 1)
    {
        if (!extract_and_insert(priority_queue))
        {
            heap_delete(priority_queue, free_nested);
            return NULL;
        }
    }
    huffman_root = (node_t *)(priority_queue->heapArr[1]);
    heap_delete(priority_queue, NULL);
}