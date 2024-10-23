#include "heap.h"

/**
 * swap - swaps two pointers
 * @a: pointer 1
 * @b: pointer 2
 */
void swap(void *a, void *b)
{
    void *c;
    c = a;
    a = b;
    b = c;
}

/**
 * sift_down - adjust heap to make it minHeap
 * @heap: heap to adjust
 */
void sift_down(heap_t *heap)
{
    int l, i, l_cmp, r_cmp, smaller;
    i = 1;
    l = i * 2;
    while (l + 1 <= heap->size || l <= heap->size)
    {
        l_cmp = heap->data_cmp(heap->heapArr[i]->data, heap->heapArr[l]->data);
        if (l + 1 <= heap->size)
        {
            r_cmp = heap->data_cmp(heap->heapArr[i]->data, heap->heapArr[l + 1]->data);
            if (l_cmp <= 0 && r_cmp <= 0)
                return;
            else
                smaller = l_cmp < r_cmp ? l : l + 1;
        }
        else
        {
            if (l_cmp <= 0)
                return;
            smaller = l;
        }
        swap(heap->heapArr[i]->data, heap->heapArr[smaller]->data);
        i = smaller;
    }
}

/**
 * heap_extract - pops root from heap
 * @heap: heap to extract root from
 * Return: pointer to data in node or NULL on failure
 */
void *heap_extract(heap_t *heap)
{
    node_t *bottom, *top;
    void *data;
    if (!heap)
        return NULL;
    if (!heap->size)
        return NULL;
    top = heap->heapArr[1];
    data = top->data;
    if (heap->size == 1)
    {
        free(heap->heapArr[1]);
        heap->heapArr[1] = NULL;
        heap->size--;
        return data;
    }
    bottom = heap->heapArr[heap->size];
    swap(bottom->data, heap->heapArr[1]->data);
    free(bottom);
    heap->heapArr[heap->size] = NULL;
    heap->size--;
    sift_down(heap);
    return data;
}

/**
 * sift_up - moves new node up the heap to right position
 * @heap: heap to sift
 */
void sift_up(heap_t *heap)
{
    int cmp, b = heap->size;
    int parent = b / 2;
    while (parent >= 1)
    {
        cmp = heap->data_cmp(heap->heapArr[b]->data, heap->heapArr[parent]->data);
        if (cmp < 0)
        {
            swap(heap->heapArr[parent]->data, heap->heapArr[b]->data);
            b = parent;
            parent = b / 2;
        }
        else
            return;
    }
}

/**
 * heap_insert - adds node to heap
 * @heap: heap to add node to 
 * @data: data to add to node
 * Return: pointer to inserted node else NULL
 */
node_t *heap_insert(heap_t *heap, void *data)
{
    node_t *new_node;
    if (!heap || !data)
        return NULL;
    if (heap->size = 0)
    {
        new_node = create_node(NULL, data);
        if (!new_node)
            return NULL;
        heap->heapArr[++heap->size] = new_node;
        return new_node;
    }
    new_node = create_node(heap->heapArr[heap->size], data);
    if (!new_node)
        return NULL;
    heap->heapArr[++heap->size] = new_node;
    sift_up(heap);
    return new_node;
}

/**
 * extract_and_insert - extract two nodes and add one node to heap
 * @heap: heap to perform function on
 * Return: inserted node or NULL on failure
 */
node_t *extract_and_insert(heap_t *heap)
{
    node_t *left, *right, *new_node;
    symbol_t *new_symbol;
    int new_freq;
    if (!heap || !heap->size)
        return NULL;
    left = (node_t *)heap_extract(heap);
    if (!left)
        return NULL;
    right = (node_t *)heap_extract(heap);
    if (!right)
    {
        free(left);
        return NULL;
    }
    new_freq = ((symbol_t *)left->data)->freq + ((symbol_t *)right->data)->freq;
    new_symbol = create_symbol(-1, new_freq);
    if (!new_symbol)
    {
        free(left);
        free(right);
        return NULL;
    }
    new_node = create_node(NULL, new_symbol);
    if (!new_node)
    {
        free(left);
        free(right);
        free(new_symbol);
        return NULL;
    }
    new_node->left = left;
    new_node->right = right;
    heap_insert(heap, new_node);
    return new_node;
}