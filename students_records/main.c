#include "rbtrees.h"

// create tree, add, delete, search for student

int add_student_record(rb_tree_t *system);
int delete_student_record(rb_tree_t *system);
node_t *find_student(rb_tree_t *system);

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
    printf("4. Display all students records\n");
    printf("5. Exit program\n");
}

/**
 * main - test Red Black trees as system for organizing data
 * Return: 0 on sucees or 1 on failure
 */
int main(void)
{
    int status;
    node_t *student;
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
            free_tree(system->root);
            free(system);
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
            else
                printf("Student record deleted\n");
            break;
        case 3:
            student = find_student(system);
            if (!student)
            {
                fprintf(stderr, "Could not locate student's record.\n");
            }
            else
            {
                printf("Record Found!\n");
                printf("ID: %d, Name: %s, Grade: %c\n", student->ID, student->name, student->grade);
            }
            break;
        case 4:
            inorder_traversal(system->root);
            break;
        case 5:
            printf("Exiting program...\n");
            free_tree(system->root);
            free(system);
            return 0;
        default:
            printf("Invalid choice. Please select a valid option.\n");
            break;
        }
    }
}


int add_student_record(rb_tree_t *system)
{
    char *name = malloc(100 * sizeof(char));
    int ID, success;
    char grade;
    if (!system)
        return 0;
    printf("Create new record:\n");

    printf("Enter student name: ");
    scanf(" %[^\n]s", name);
    while (getchar() != '\n');

    printf("Enter student ID: ");
    scanf("%d", &ID);
    while(getchar() != '\n');
    
    printf("Enter student grade: ");
    scanf("%c", &grade);
    while(getchar() != '\n');

    success = insert(system, ID, name, grade);
    if (!success)
    {
        free(name);
        return 0;
    }
    printf("Added new student recorcd!\n\n");
    free(name);
    return 1;
}

int delete_student_record(rb_tree_t *system)
{
    char *name = malloc(100 * sizeof(char));
    int is_deleted;
    if (!system)
        return 0;
    printf("Delete record:\n");

    printf("Enter student name: ");
    scanf(" %[^\n]s", name);
    while (getchar() != '\n');

    is_deleted = delete_node(system, system->root, name);
    if (!is_deleted)
    {
        free(name);
        return 0;
    }
    free(name);
    return 1;
}

node_t *find_student(rb_tree_t *system)
{
    int ID;
    if (!system)
        return NULL;
    printf("Find a student record:\n");

    printf("Enter student ID: ");
    scanf("%d", &ID);
    while(getchar() != '\n');

    return search_tree(system->root, ID);
}