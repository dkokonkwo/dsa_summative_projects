#ifndef RBTREES_H
#define RBTREES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct node_s - structure for storing student's record
 * @ID: student's ID
 * @name: Student's name
 * @grade: student's grade
 * @left: pointer to left child
 * @right: pointer to right child
 * @parent: pointer to parent
 * @color: color of node(red: 0, black: 1)
 */
typedef struct node_s
{
    int ID;
    char *name;
    char grade;
    struct node_s *left;
    struct node_s *right;
    struct node_s *parent;
    int color;
} node_t;

/**
 * struct rb_tree_s - stucture for red black tree
 * @root: root of the tree
 * @size: number of node in tree
 */
typedef struct rb_tree_s
{
    node_t *root;
    int size;
} rb_tree_t;

#endif