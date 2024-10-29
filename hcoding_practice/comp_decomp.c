#include "heap.h"

/**
 * compresses a file
 * @filename
 * @tree: huffman tree
 * @code: huffman codes
 * Return: 1 on success, 0 on failure
 */
int compress_file(const char *filename, node_t *tree, char *codes[])
{
    FILE *input = fopen(filename, "r");
    FILE *output = fopen("compressed.bin", "wb");
    if (!input || !output)
    {
        printf("Error opening files\n");
        return 0;
    }
    int ch;
    while ((ch = fgetc(input)) != EOF)
    {
        if (isprint(ch))
        {
            fputs(codes[ch], output);
        }
    }
    fclose(input);
    fclose(output);
    printf("File compressed succesfully\n");
    return 1;
}

/**
 * decompress_file - decompresses file using huffman treee
 * 
 */