#include "dictionary.h"

/**
 * create_dict - creates new dictionary
 * Return: pointer to created dictionary else NULL
 */
dict_t *create_dict(void)
{
    dict_t *new_dict = (dict_t *)malloc(sizeof(dict_t));
    if (!new_dict)
        return NULL;
    new_dict->root = NULL;
    new_dict->nb_words = 0;
    return new_dict;
}

/**
 * add_word - add new word to dictionary
 * @dict: dictionary
 * @word: word
 * @def: word definition
 * Return: 1 on success else 0 on failure
 */
int add_word(dict_t *dict, char *word, char *def)
{
    if (!dict || !word || !def)
        return 0;
    node_t *new_word = (node_t *)malloc(sizeof(node_t));
    if (!new_word)
        return 0;
    new_word->word = strdup(word);
    if (!new_word->word)
    {
        free(new_word);
        return 0;
    }
    new_word->def = strdup(def);
    if (!new_word->def)
    {
        free(new_word->word);
        free(new_word);
        return 0;
    }
    new_word->left = NULL;
    new_word->right = NULL;
    if (!dict->root)
    {
        dict->root = new_word;
        new_word->index = dict->nb_words++;
        return 1;
    }
    node_t *curr = dict->root;
    int val;
    while (curr)
    {
        val = strcasecmp(word, curr->word);
        if (val < 0)
        {
            if (curr->left)
                curr = curr->left;
            else
            {
                curr->left = new_word;
                break;
            }
        }
        else if (val > 0)
        {
            if (curr->right)
                curr = curr->right;
            else
            {
                curr->right = new_word;
                break;
            }
        }
        else
        {
            printf("%s already exists in dictionary.\n", word);
            free(new_word->word);
            free(new_word->def);
            free(new_word);
            return 0;
        }
    }
    new_word->index = dict->nb_words++;
    return 1;
}

/**
 * search_word - find definition of word in dictionary
 * @dict: dictionary
 * @word: word to search for
 * Return: pointer to word else NULL
 */
node_t *search_word(dict_t *dict, char *word)
{
    if (!dict || !word)
        return NULL;
    node_t *curr = dict->root;
    int val;
    while (curr)
    {
        val = strcasecmp(word, curr->word);
        if (val < 0)
            curr = curr->left;
        else if (val > 0)
            curr = curr->right;
        else
            return curr;
    }
    return NULL;
}

/**
 * disp_dict - displays all words in dictionary(in order traversal)
 * @root: current pointer to word
 */
void disp_dict(node_t *root)
{
    if (!root)
        return;
    if (!root->word)
        return;
    disp_dict(root->left);
    printf("%s\n", root->word);
    disp_dict(root->right);
}

/**
 * swap - swap function for deleting
 * @node1: first node
 * @node2: second node
 */
void swap(node_t *node1, node_t* node2)
{
    char *temp_word = node1->word;
    char *temp_def = node1->def;
    size_t temp_index = node1->index;

    node1->word = node2->word;
    node1->def = node2->def;
    node1->index = node2->index;

    node2->word = temp_word;
    node2->def = temp_def;
    node2->index = temp_index;
}

/**
 * find_min - gets the minimum value node in subtree
 * @node: root of subtree to search
 * Return: pointer to minimum value
 */
node_t *find_min(node_t *node)
{
    node_t *current;
    if (!node)
        return NULL;
    current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

/**
 * del_word - delete a word in dictionary
 * @root: dictionary root
 * @word: word to delete
 * Return: dictionary root
 */
node_t *del_word(node_t *root, char *word)
{
    node_t *temp;
    if (!root)
        return root;
    if (strcasecmp(word, root->word) < 0)
        root->left = del_word(root->left, word);
    else if (strcasecmp(word, root->word) > 0)
        root->right = del_word(root->right, word);
    else
    {
        if (!root->left && !root->right)
        {
            free(root->word);
            free(root->def);
            free(root);
            return NULL;
        }
        else if (root->left == NULL)
        {
            temp = root->right;
            free(root->word);
            free(root->def);
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            temp = root->left;
            free(root->word);
            free(root->def);
            free(root);
            return temp;
        }

        temp = find_min(root->right);
        free(root->word);
        free(root->def);
        root->word = strdup(temp->word);
        root->def = strdup(temp->def);
        root->right = del_word(root->right, temp->word);
    }
    return root;
}

/**
 * del_dict - deletes dictionary
 * @dict: dictionary
 */
void del_dict(dict_t *dict)
{
    if (!dict || !dict->root)
        return;
    del_dict_nodes(dict->root);
    free(dict);
}

/**
 * del_dict_nodes - helper function to delete all nodes in the dictionary
 * @root: root node of the dictionary
 */
void del_dict_nodes(node_t *root)
{
    if (!root)
        return;

    del_dict_nodes(root->left);
    del_dict_nodes(root->right);

    free(root->word);
    free(root->def);
    free(root);
}
