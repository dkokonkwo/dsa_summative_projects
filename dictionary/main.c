#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

/**
 * display_menu: Function to display menu options
 */
void display_menu(void)
{
    printf("\n--- Dictionary Menu ---\n");
    printf("1. Add word to dictionary\n");
    printf("2. Delete word from dictionary\n");
    printf("3. Search for a word's definition\n");
    printf("4. Display all words in dictionary (alphabetical order)\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

/**
 * Main function to interact with the user
 */
int main(void)
{
    dict_t *dictionary = create_dict();
    if (!dictionary)
    {
        printf("Failed to create the dictionary.\n");
        return EXIT_FAILURE;
    }

    int choice;
    char word[100];
    char def[256];

    while (1)
    {
        display_menu();
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                printf("Enter the word: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = '\0';

                printf("Enter the definition: ");
                fgets(def, sizeof(def), stdin);
                def[strcspn(def, "\n")] = '\0';

                if (add_word(dictionary, word, def))
                    printf("Word added successfully!\n");
                else
                    printf("Failed to add word to the dictionary.\n");
                break;

            case 2:
                printf("Enter the word to delete: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = '\0';

                node_t *word_to_delete = search_word(dictionary, word);
                if (word_to_delete)
                {
                    del_word(dictionary, word_to_delete);
                    printf("Word deleted successfully!\n");
                }
                else
                {
                    printf("Word not found in the dictionary.\n");
                }
                break;

            case 3:
                printf("Enter the word to search: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = '\0';

                node_t *search_result = search_word(dictionary, word);
                if (search_result)
                    printf("Definition of '%s': %s\n", word, search_result->def);
                else
                    printf("Word not found in the dictionary.\n");
                break;

            case 4:
                printf("\nWords in the dictionary (alphabetical order):\n");
                disp_dict(dictionary->root);
                break;

            case 5:
                printf("Exiting the program. Deleting the dictionary...\n");
                del_dict(dictionary);
                printf("Dictionary deleted. Goodbye!\n");
                return EXIT_SUCCESS;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return EXIT_SUCCESS;
}
