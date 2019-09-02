/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** linked_list_alias
*/

#include "mysh.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

l_list_t *init_list(char *old, char *new)
{
    l_list_t *head = malloc(sizeof(l_list_t));

    if (!head)
        exit(84);
    head->new = strdup(new);
    head->old = strdup(old);
    head->next = NULL;
    head->prev = NULL;
    free(new);
    free(old);
    return (head);
}

void new_node(l_list_t *list, char *old, char *new)
{
    l_list_t *new_node;

    if (!old || !new)
        exit(84);
    new_node = malloc(sizeof(l_list_t));
    if (!new_node)
        exit(84);
    new_node->new = strdup(new);
    new_node->old = strdup(old);
    new_node->next = NULL;
    for (; list->next != NULL;)
            list = list->next;
    new_node->prev = list;
    list->next = new_node;
    free(new);
    free(old);
}
