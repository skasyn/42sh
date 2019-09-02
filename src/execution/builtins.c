/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** builtins.c
*/

#include <string.h>
#include "execute.h"

int find_builtins(char *str)
{
    for (int i = 0; i < BUILTINS_NB; ++i) {
        if (strcmp(builtins[i].str, str) == 0)
            return (i);
    }
    return (-1);
}

int builtin_exit(shell_t *shell, ll_tree_t *node)
{
    (void)node;
    shell->end = 1;
    return (0);
}

int check_builtins(shell_t *shell, ll_tree_t *node)
{
    int builtin_nb = find_builtins(node->argv[0]);

    if (builtin_nb == -1)
        return (0);
    shell->return_value = builtins[builtin_nb].function(shell, node);
    return (1);
}