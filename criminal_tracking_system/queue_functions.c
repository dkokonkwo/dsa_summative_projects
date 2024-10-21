#include "graph.h"


/**
 * create_queue - create a queue data structure
 * Return: created empty queue
 */
queue_t *create_queue(void)
{
queue_t *queue = (queue_t *) malloc(sizeof(queue_t));
if (!queue)
{
return (NULL);
}

queue->nb_nodes = 0;
queue->head = NULL;
queue->tail = NULL;

return (queue);
}

/**
 * enqueue - add node to queue
 * @q: queue to add node to
 * @v: vertex of the node
 */
void enqueue(queue_t *q, vertex_t *v)
{
node_t *new_node;
if (!q || !v)
{
return;
}
new_node = (node_t *) malloc(sizeof(node_t));
if (!new_node)
{
return;
}
new_node->vertex = v;
new_node->next = NULL;
if (q->nb_nodes == 0)
{
q->head = new_node;
q->tail = new_node;
}
else
{
q->tail->next = new_node;
q->tail = new_node;
}
q->nb_nodes++;
}

/**
 * dequeue - pops first node from queue
 * @q: queue to pop from
 * Return: vertex of node
 */
vertex_t *dequeue(queue_t *q)
{
node_t *temp_node;
vertex_t *vertex;
if (!q || q->nb_nodes == 0)
{
return (NULL);
}
temp_node = q->head;
vertex = temp_node->vertex;
q->head = temp_node->next;
if (!q->head)
    q->tail = NULL;
free(temp_node);
q->nb_nodes--;
return (vertex);
}
