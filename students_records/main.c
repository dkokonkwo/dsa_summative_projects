#include "rbtrees.h"

// create tree, add, delete, search for student
/**
 * display_menu - user input menu
 */
void display_menu(void)
{
    printf("DYNAMIC STUDENTS' RECORDS MANAGEMENT SYSTEM\n");
    printf("Computer Science Freshmen Records\n");
    printf("1. Add student record to system\n");
    printf("2. Delete student record from system\n");
    printf("3. Search for student record in system\n");
    printf("4. Exit program\n");
}

/**
 * main - test Red Black trees as system for organizing data
 * Return: 0 on sucees or 1 on failure
 */
int main(void)
{
    int status;
    rb_tree_t *system = build_tree();
    if (!system)
    {
        fprintf(stderr, "Could not spin up system. Try again.\n");
        return 1;
    }
    while (1)
    {
        display_menu();
        printf("Enter your choice: ");
        if (scanf("%d", &status) != 1)
        {
            fprintf(stderr, "Invalid input. Exiting...\n");
            return 1;
        }

        while(getchar() != '\n')
            ;
        switch (status)
        {
        case 1:
            status = add_student_record(system);
            if (!status)
            {
                fprintf(stderr, "Failed to add student records.\n");
            }
            break;
        case 2:
            status = delete_student_record(system);
            if (!status)
            {
                fprintf(stderr, "Failed to delete student records.\n");
            }
            break;
        case 3:
            inorder_traversal(system->root);
            break;
        case 4:
            printf("Exiting program...\n");
            tree_delete(system);
            return 0;
        default:
            break;
        }
    }
}