#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * struct node_s - word structure
 * @word: word
 * @def: definition of word
 * @index: index of word in dictionary
 * @left: pointer to left child
 * @right: pointer to right child
 */
typedef struct node_s
{
    char *word;
    char *def;
    size_t index;
    struct node_s *left;
    struct node_s *right;
} node_t;

/**
 * struct dict_s - structure for dictionary
 * @nb_words: number of words in dictionary
 * @root: pointer to root node in dictionary
 */
typedef struct dict_s
{
    size_t nb_words;
    node_t *root;
} dict_t;


dict_t *create_dict(void);
int add_word(dict_t *dict, char *word, char *def);
node_t *search_word(dict_t *dict, char *word);
void disp_dict(node_t *root);
node_t *find_min(node_t *node);
node_t *del_word(node_t *root, char *word);
void del_dict(dict_t *dict);
void swap(node_t *node1, node_t* node2);
void del_dict_nodes(node_t *root);
#endif
