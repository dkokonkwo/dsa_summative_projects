#include "tasks.h"

/**
 * create_todo_list - creates new todoList
 * Return: pointer to todoList else NULL on failure
 */
todoList *create_todo_list(void)
{
    todoList *new_todo = (todoList *)malloc(sizeof(todoList));
    if (!new_todo)
        return NULL;
    new_todo->nb_tasks = 0;
    new_todo->head = NULL;
    new_todo->tail = NULL;
    return new_todo;
}

/**
 * add_task - adds task to todoList
 * @todo_list: todo list
 * @desc: task description
 * Return: pointer to added task else NULL
 */
listNode *add_task(todoList *todo_list, char *desc)
{
    if (!desc)
        return NULL;
    listNode *new_task = (listNode *)malloc(sizeof(listNode));
    if (!new_task)
        return NULL;
    new_task->desc = strdup(desc);
    new_task->next = NULL;
    if (!new_task->desc)
    {
        free(new_task);
        return NULL;
    }
    if (!todo_list->head)
    {
        todo_list->head = new_task;
        todo_list->tail = new_task;
    }
    else
    {
        todo_list->tail->next = new_task;
        todo_list->tail = new_task;
    }
    new_task->ID = ++todo_list->nb_tasks;
    return new_task;
}

/**
 * delete_task - removes task from list by ID
 * @todo_list: todo list
 * @ID: task ID
 * Return: 1 on success else 0
 */
int delete_task(todoList *todo_list, int ID)
{
    if (!todo_list || ID <= 0)
        return 0;
    listNode *curr, *prev = NULL;
    for (curr = todo_list->head; curr; curr = curr->next)
    {
        if (curr->ID == ID)
        {
            if (prev)
                prev->next = curr->next;
            else
                todo_list->head = curr->next;
            if (curr == todo_list->tail)
                todo_list->tail = prev;
            free(curr->desc);
            free(curr);
            return 1;
        }
        prev = curr;
    }
    return 0;
}

/**
 * display_tasks - displays all tasks
 * @todo_list: todo list
 */
void display_tasks(todoList *todo_list)
{
    if (todo_list)
    {
        listNode *curr;
        printf("ID\t TASK DESCRIPTION\n");
        for (curr = todo_list->head; curr; curr = curr->next)
        {
            printf("%d.\t %s\n", curr->ID, curr->desc);
        }
    }
}

/**
 * delete_list - deletes todo list
 * @todo_list: todo list to delete
 */
void delete_list(todoList *todo_list)
{
    if (todo_list)
    {
        listNode *curr, *temp;
        for (curr = todo_list->head; curr; curr = temp)
        {
            temp = curr->next;
            free(curr->desc);
            free(curr);
        }
        free(todo_list);
    }
}
