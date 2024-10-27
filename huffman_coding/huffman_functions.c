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
 * Return: pointer to priorty queue of huffman tree or NULL on failure
 */
heap_t *build_huffman_tree(char *sym_arr, int *freq_arr, int size)
{
    heap_t *priority_queue;
    if (!sym_arr || !freq_arr || size < 1)
        return NULL;
    priority_queue = create_priority_queue(sym_arr, freq_arr, size);
    if (!priority_queue)
        return NULL;
    while (priority_queue->nb_nodes > 1)
    {
        if (!extract_and_insert(priority_queue))
        {
            heap_delete(priority_queue, free_nested);
            return NULL;
        }
    }
    return priority_queue;
}


void print_tree(node_t *root)
{
    char dol;
    symbol_t *sym;
    if (!root)
        return;
    sym = (symbol_t *)root->data;
    if (sym->data == -1)
        dol = '$';
    else
        dol = sym->data;
    printf("%c, %d\n", dol, sym->freq);
    print_tree(root->left);
    print_tree(root->right);
}

void huffman_code(node_t *root, char *code, int level)
{
    symbol_t *sym;
    char *code_next;
    if (!root)
        return;
    /* leaf node */
    if (!root->left && !root->right)
    {
        sym = (symbol_t *)root->data;
        printf("%c: %s\n", sym->data, code);
        return;
    }
    if (root->left)
    {
        code_next = strdup(code);
        code_next[level] = '0';
        huffman_code(root->left, code_next, level + 1);
    }
    if (root->right)
    {
        code_next = strdup(code);
        code_next[level] = '1';
        huffman_code(root->right, code_next, level + 1);
    }
}