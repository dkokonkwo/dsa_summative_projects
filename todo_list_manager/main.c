#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tasks.h"

void show_menu(void);

int main(void)
{
    todoList *my_todo_list = create_todo_list();
    if (!my_todo_list)
    {
        printf("Error: Could not create the to-do list\n");
        return 1;
    }

    int choice, task_id, del_id;
    char task_desc[256];

    while (1)
    {
        show_menu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                printf("Enter task description: ");
                getchar();
                fgets(task_desc, sizeof(task_desc), stdin);
                task_desc[strcspn(task_desc, "\n")] = '\0';

                if (add_task(my_todo_list, task_desc))
                {
                    printf("Task added successfully.\n");
                }
                else
                {
                    printf("Error: Could not add the task.\n");
                }
                break;

            case 2:
                printf("Enter the task ID to delete: ");
                if (scanf("%d", &task_id) != 1)
                {
                    printf("Invalid input. Please enter a valid task ID.\n");
                    while (getchar() != '\n');
                    continue;
                }

                if (delete_task(my_todo_list, task_id))
                {
                    printf("Task deleted successfully.\n");
                }
                else
                {
                    printf("Task with ID %d not found.\n", task_id);
                }
                break;
            
            case 3:
                printf("Enter the ID of completed task\n");
                if (scanf("%d", &del_id) != 1)
                {
                    printf("Invalid input. Please enter a valid task ID.\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (delete_task(my_todo_list, del_id))
                {
                    printf("Task complete! Well done.\n");
                }
                else
                {
                    printf("Task with ID %d not found.\n", del_id);
                }
                break;

            case 4:
                printf("\nTo-Do List:\n");
                display_tasks(my_todo_list);
                break;

            case 5:
                printf("Exiting the to-do list program. Goodbye!\n");
                delete_list(my_todo_list);
                return 0;

            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    }
    return 0;
}

/**
 * show_menu - Displays the menu options for the user
 */
void show_menu(void)
{
    printf("\nTo-Do List Menu:\n");
    printf("1. Add a task\n");
    printf("2. Delete a task\n");
    printf("3. Mark task as completed\n");
    printf("4. Display all tasks\n");
    printf("5. Exit\n");
}
