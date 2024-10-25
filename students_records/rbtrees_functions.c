#include "rbtrees.h"

// add, delete, update, inorder traversal of node
// create rb_tree

/**
 * rb_tree_create - creates new rb_tree
 * Return: pointer to tree else NULL on failure
 */
rb_tree_t *rb_tree_create(void)
{
    rb_tree_t *rb_tree = (rb_tree_t *)malloc(sizeof(rb_tree_t));
    if (!rb_tree)
        return NULL;
    rb_tree->root = NULL;
    rb_tree->size = 0;
    return rb_tree;
}

/**
 * inorder_traversal - prints/visits nodes in order
 * @node: pointer to node to visit
 */
void inorder_traversal(node_t *node)
{
    if (!node)
        return;
    inorder_traversal(node->left);
    printf("ID: %d, Name: %s, Grade: %d\n", node->ID, node->name, node->grade);
    inorder_traversal(node->right);
}

/**
 * search_tree - search for node in tree
 * @node: pointer to current node
 * @ID: id of node to search for
 * Return: pointer to node if found else NULL on failure
 */
node_t *search_tree(node_t *node, int ID)
{
    node_t *left, *right;
    if (!node)
        return NULL;
    if (node->ID == ID)
        return node;
    left = search_tree(node->left, ID);
    right = search_tree(node->right, ID);
    return left ? left : right;
}


/**
 * insert_fix - balances trees after insertion
 * @tree: pointer to tree
 * @node: pointer to inserted node
 */
void insert_fix(rb_tree_t *tree, node_t *node)
{
    node_t *temp;
    while (node->parent && node->parent->color == 1)
    {
        if (node->parent == node->parent->parent->right)
        {
            temp = node->parent->parent->left;
            if (temp && temp->color == 1)
            {
                temp->color = 0;
                node->parent->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    right_rotate(tree, node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                left_rotate(tree, node->parent->parent);
            }
        }
        else
        {
            temp = node->parent->parent->right;
            if (temp->color == 1)
            {
                temp->color = 0;
                node->parent->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    left_rotate(tree, node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                right_rotate(tree, node->parent->parent);
            }
        }
        if (node == tree->root)
            break;   
    }
    tree->root->color = 0;
}

/**
 * insert - inserts new node into tree
 * @tree: pointer to tree to insert node
 * @ID: student ID
 * @name: student name
 * @grade: student grade
 * Return: 1 on success else 0
 */
int insert(rb_tree_t *tree, int ID, char *name, char grade)
{
    node_t *x, *y = NULL;
    if (!tree || !name)
        return 0;
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (!node)
        return 0;
    node->name = strdup(name);
    if (!node->name)
    {
        free(node);
        return 0;
    }
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->ID = ID;
    node->grade = grade;
    node->color = 1;
    x = tree->root;
    while (x)
    {
        y = x;
        if (strcasecmp(node->name, x->name) < 0)
            x = x->left;
        else
            x = x->right;
    }
    node->parent = y;
    if (!y)
        tree->root = node;
    else if (strcasecmp(node->name, y->name) < 0)
        y->left = node;
    else
        y->right = node;
    
    if (node->parent == NULL)
        node->color = 0;
    if (node->parent->parent == NULL)
        return 1;
    insert_fix(tree, node);
    return 1;
}

/**
 * rb_transplant - moves position of a node to another place
 * @tree: pointer to tree
 * @n1: pinter to first node
 * @n2: pointer to second node
 */
void rb_transplant(rb_tree_t *tree, node_t *n1, node_t *n2)
{
    if (!n1->parent)
        tree->root = n2;
    else if (n1 == n1->parent->left)
        n1->parent->left = n2;
    else
        n1->parent->right = n2;
    n2->parent = n1->parent;
}


/**
 * delete_fix - balances tree after deletetion
 * @tree: pointer to tree
 * @node: pointer to node to fix
 */
void delete_fix(rb_tree_t *tree, node_t *node)
{
    node_t *temp;
    while (node != tree->root && node->color == 0)
    {
        if (node == node->parent->left)
        {
            temp = node->parent->right;
            if (temp->color == 1)
            {
                temp->color = 0;
                node->parent->color = 1;
                left_rotate(tree, node->parent);
                temp = node->parent->right;
            }
            if (temp->left->color == 0 && temp->right->color == 0)
            {
                temp->color = 1;
                node = node->parent;
            }
            else
            {
                if (temp->right->color == 0)
                {
                    temp->left->color = 0;
                    temp->color = 1;
                    right_rotate(tree, temp);
                    temp = node->parent->right;
                }
                temp->color = node->parent->color;
                node->parent->color = 0;
                temp->right->color = 0;
                left_rotate(tree, node->parent);
                node = tree->root;
            }
        }
        else
        {
            temp = node->parent->left;
            if (temp->color == 1)
            {
                temp->color = 0;
                node->parent->color = 1;
                right_rotate(tree, node->parent);
                temp = node->parent->left;
            }
            if (temp->left->color == 0 && temp->right->color == 0)
            {
                temp->color = 1;
                node = node->parent;
            }
            else
            {
                if (temp->left->color == 0)
                {
                    temp->right->color = 0;
                    temp->color = 1;
                    left_rotate(tree, temp);
                }
                temp->color = node->parent->color;
                node->parent->color = 0;
                temp->left->color = 0;
                right_rotate(tree, node->parent);
                node = tree->root;
            }
        }
    }
    node->color = 0;
}

/**
 * delete_node - deletes node from tree
 * @tree: pointer to tree
 * @node: pointer to root node of tree
 * @name: student name
 * Return: 1 on success else 0
 */
int delete_node(rb_tree_t *tree, node_t *node, char *name)
{
    node_t *x, *y, *z = NULL;
    if (!node || !name)
        return 0;
    while (node != NULL)
    {
        if (strcasecmp(node->name, name) == 0)
        {
            z = node;
            break;
        }
        else if (strcasecmp(node->name, name) < 0)
            node = node->right;
        else
            node = node->left;
    }
    if (z == NULL)
    {
        printf("Name was not found in records");
        return 0;
    }
    y = z;
    int y_original_color = y->color;
    if (z->left == NULL)
    {
        x = z->right;
        rb_transplant(tree, z, z->right);
    }
    else if (z->right == NULL)
    {
        x = z->left;
        rb_transplant(tree, z, z->left);
    }
    else
    {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            rb_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rb_transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free_node(z);
    if (y_original_color == 0)
        delete_fix(tree, x);
}

/**
 * minimum - smallest left leaf node
 * @node: pointer to node
 * Return: pointer to leftmost leaf node
 */
node_t *minimum(node_t *node)
{
    while(node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

/**
 * maximum - smallest right leaf node
 * @node: pointer to node
 * Return: pointer to rightmost leaf node
 */
node_t *maximum(node_t *node)
{
    while(node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

/**
 * left_rotate - rotate node and parent anticlockwis
 * @tree: pointer to tree
 * @node: pointer to node
 */
void left_rotate(rb_tree_t *tree, node_t *node)
{
    if (!tree || !node)
        return;
    node_t *y = node->right;
    node->right = y->left;
    if (y->left != NULL) 
      y->left->parent = node;
    y->parent = node->parent;
    if (node->parent == NULL)
      tree->root = y;
    else if (node == node->parent->left)
      node->parent->left = y;
    else
      node->parent->right = y;
    y->left = node;
    node->parent = y;
    tree->root->color = 0;
}

/**
 * right_rotate - rotate node and parent clockwise
 * @tree: pointer to tree
 * @node: pointer to node
 */
void right_rotate(rb_tree_t *tree, node_t *node)
{
    if (!tree || !node)
        return;
    node_t *y = node->left;
    node->left = y->right;
    if (y->right != NULL)
        y->right->parent = node;
    y->parent = node->parent;
    if (node->parent == NULL)
        tree->root = y;
    else if (node == node->parent->right)
        node->parent->right = y;
    else
        node->parent->left = y;
    y->right = node;
    node->parent = y;
    tree->root->color = 0;
}

/**
 * free_node - frees node
 * @node: pointer to node to free
 */
void free_node(node_t *node)
{
    if (node)
    {
        free(node->name);
        free(node);
    }
}