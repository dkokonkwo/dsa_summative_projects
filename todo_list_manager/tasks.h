#ifndef TASKS_H
#define TASKS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * struct listNode - node that stores task
 * @desc: task description
 * @ID: task ID
 * @prev: pointer to previous task
 * @next: pointer to next task
 */
typedef struct listNode
{
    char *desc;
    int ID;
    struct listNode *next;
} listNode;

/**
 * struct todoList - todo list structure
 * @nb_tasks: number of tasks in todoList
 * @head: first task in todoList
 */
typedef struct todoList
{
    int nb_tasks;
    listNode *head;
    listNode *tail;
} todoList;

todoList *create_todo_list(void);
listNode *add_task(todoList *todo_list, char *desc);
int delete_task(todoList *todo_list, int ID);
void display_tasks(todoList *todo_list);
void delete_list(todoList *todo_list);
#endif
