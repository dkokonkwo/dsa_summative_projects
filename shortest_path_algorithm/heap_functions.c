#include "graph.h"

/**
 * heap_create - create heap structure
 * Return: pointer to heap or NULL on failure
 */
heap_t *heap_create(void)
{
    vertex_t **arr;
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    if (!heap)
        return NULL;
    heap->nb_vertices = 0;
    heap->size = 2;
    arr = (vertex_t **)malloc(heap->size * sizeof(vertex_t *));
    if (!arr)
        return NULL;
    heap->heapArr = arr;
    return heap;
}

/**
 * swap - swaps positions of two vertices in heap
 * @p1: postion 1
 * @p2: postion 2
 */
void swap(heap_t *heap, int p1, int p2)
{
    vertex_t *temp;
    temp = heap->heapArr[p1];
    heap->heapArr[p1] = heap->heapArr[p2];
    heap->heapArr[p2] = temp;
}

/**
 * sift_up - moves new node up the heap to right position
 * @heap: heap to sift
 * @position: index to start sift
 */
void sift_up(heap_t *heap, size_t position)
{
    int cmp;
    int b = (int)position;
    int parent = b / 2;
    while (parent >= 1)
    {
        cmp = heap->heapArr[b]->value - heap->heapArr[parent]->value;
        if (cmp >= 0)
            break;
        swap(heap, parent, b);
        b = parent;
        parent = b / 2;
    }
}

void heap_sort(heap_t *heap)
{
    size_t i, j, min;
    int a, b;
    if (!heap)
        return;
    if (!heap->nb_vertices)
        return;
    for (i = 1; i < heap->nb_vertices; i++)
    {
        min = i;
        for (j = i + 1; j <= heap->nb_vertices; j++)
        {
            if (heap->heapArr[j]->value < heap->heapArr[min]->value)
            {
                min = j;
            }
        }
        a = (int)i;
        b = (int)min;
        swap(heap, a, b);
    }
}

/**
 * enqueue - adds vertex to heap
 * @heap: pointer to heap
 * @vertex: vertex to add to heap
 */
void enqueue(heap_t *heap, vertex_t *vertex)
{
    vertex_t **arr;
    if (!heap || !vertex)
        return;
    /* resize array if full*/
    if (heap->size - heap->nb_vertices == 1)
    {
        arr = realloc(heap->heapArr, heap->size * 2 * sizeof(vertex_t *));
        if (!arr)
        {
            printf("Could not expand array\n");
            return;
        }
        heap->heapArr = arr;
        heap->size *= 2;
    }
    heap->heapArr[++heap->nb_vertices] = vertex;
}

/**
 * sift_down - move vertex down min heap
 * @heap: pointer to min heap/priority_queue
 */
void sift_down(heap_t *heap)
{
    int l_cmp, r_cmp, smaller;
    size_t l, i;
    i = 1;
    l = i * 2;
    while (l + 1 <= heap->nb_vertices || l <= heap->nb_vertices)
    {
        l_cmp = heap->heapArr[i]->value - heap->heapArr[l]->value;
        if (l + 1 <= heap->nb_vertices)
        {
            r_cmp = heap->heapArr[i]->value - heap->heapArr[l + 1]->value;
            if (l_cmp <= 0 && r_cmp <= 0)
                return;
            else
                smaller = l_cmp > r_cmp ? l : l + 1;
        }
        else
        {
            if (l_cmp <= 0)
                return;
            smaller = l;
        }
        int j = (int)i;
        swap(heap, j, smaller);
        i = smaller;
    }
}

/**
 * dequeue - removes first element from min heap
 * @heap: pointer to heap
 * Return: pointer to removed element else NULL on failure
 */
vertex_t *dequeue(heap_t *heap)
{
    vertex_t *v;
    int last;
    if (!heap)
        return NULL;
    if (heap->nb_vertices == 0)
    {
        printf("Empty heap\n");
        return NULL;
    }
    v = heap->heapArr[1];
    if (heap->nb_vertices == 1)
    {
        heap->heapArr[1] = NULL;
        return v;
    }
    last = (int)heap->nb_vertices;
    swap(heap, last, 1);
    heap->heapArr[heap->nb_vertices] = NULL;
    heap->nb_vertices--;
    heap_sort(heap);
    return v;
}


void print_queue(heap_t *q)
{
    size_t i;
    if (!q)
        return;
    if (!q->nb_vertices)
        return;
    for (i = 1; i <= q->nb_vertices; i++)
    {
        printf("index: %lu, value: %d\n", q->heapArr[i]->index, q->heapArr[i]->value);
    }
    printf("\n");
}