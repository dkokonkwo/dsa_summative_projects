#include "heap.h"

#define MAX_CHAR 256

/**
 * read text from file and create arrays of symbols and freqencies
 * compress file and decompress file.
 */

/**
 * get_sym_freq_arr - get symbol and frequencies arrays
 * @file: file to get characters from
 * @chars: symbols array
 * @freq: frequencies array
 * @count: number of unique characters
 */
void get_sym_freq_arr(FILE *file, char chars[], int freq[], int *count)
{
    int ch, i;
    int found;

    while ((ch = fgetc(file)) != EOF)
    {
        if (isprint(ch))
        {
            found = 0;

            for (i = 0; i < *count; i++)
            {
                if (chars[i] == ch)
                {
                    freq[i]++;
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                chars[*count] = ch;
                freq[*count] = 1;
                (*count)++;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    node_t *node;
    heap_t *priority_queue;
    if (argc != 3)
    {
        printf("Usage: %s <filename> <compress>|<decompress>\n", argv[0]);
        return 1;
    }

    char algo = argv[2][0];
    if (algo != 'c' || algo != 'd')
    {
        printf("Usage: %s <filename> <compress>|<decompress>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Error opening file!\n");
        return 1;
    }

    char characters[MAX_CHAR] = {0};
    int frequencies[MAX_CHAR] = {0};
    int count = 0;

    get_sym_freq_arr(file, characters, frequencies, &count);

    fclose(file);

    printf("%d\n", count);

    printf("Character Frequency\n");
    for (int i = 0; i < count; i++) {
        printf("'%c' : %d\n", characters[i], frequencies[i]);
    }

    char *code = malloc(100 * sizeof(char));
    if (!code)
    {
        printf("Memory allocation error!\n");
        return 1;
    }
    int level = 0;

    priority_queue = build_huffman_tree(characters, frequencies, count);
    node = (node_t *)priority_queue->heapArr[1]->data;

    printf("\tTree:\n");
    print_tree(node);
    printf("\n\tHuffman codes:\n");
    huffman_code(node, code, level);
    printf("%d\n", level);

    free_nested(node);
    heap_delete(priority_queue, NULL);
    free(code);

    return 0;
}