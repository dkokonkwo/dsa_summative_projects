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

void right_rotate(rb_tree_t *tree, node_t *node);
void left_rotate(rb_tree_t *tree, node_t *node);
node_t *maximum(node_t *node);
node_t *minimum(node_t *node);
int delete_node(rb_tree_t *tree, node_t *node, char *name);
void delete_fix(rb_tree_t *tree, node_t *node);
void rb_transplant(rb_tree_t *tree, node_t *n1, node_t *n2);
int insert(rb_tree_t *tree, int ID, char *name, char grade);
void insert_fix(rb_tree_t *tree, node_t *node);
node_t *search_tree(node_t *node, int ID);
void inorder_traversal(node_t *node);
rb_tree_t *rb_tree_create(void);
void free_node(node_t *node);

#endif