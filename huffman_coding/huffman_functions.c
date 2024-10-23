#include "heap.h"

/**
 * create_priority_queue - creates priority queue from symbols
 * @sym_arr: array of symbols
 * @freq_arr: array of corresponding frequencies
 * @size: size of both arrays
 * Return: priority queue heap or NULL on failure
 */
heap_t *create_proirity_queue(char *sym_arr, int freq_arr, int size)
{
    heap_t *priority_queue;
    symbol_t *symbol;
    node_t *node;
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
            heap_delete(priority_queue);
    }
}