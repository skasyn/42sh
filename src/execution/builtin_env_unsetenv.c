/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** builtin_env_unsetenv.c
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "execute.h"

static void builtin_unsetenv_change(shell_t *shell, char *argv)
{
    char *to_find = NULL;
    int pos = -1;

    to_find = my_strcat(argv, "=");
    for (int i = 0; shell->env[i] != NULL; ++i) {
        if (strncmp(shell->env[i], to_find, strlen(to_find)) == 0) {
            pos = i;
            break;
        }
    }
    free(to_find);
    if (pos == -1)
        return;
    free(shell->env[pos]);
    for (int i = pos; shell->env[i] != NULL; ++i)
        shell->env[i] = shell->env[i + 1];
}

void builtin_unsetenv_all(shell_t *shell)
{
    for (int i = 0; shell->env[i] != NULL; ++i) {
        free(shell->env[i]);
        shell->env[i] = NULL;
    }
}

int builtin_unsetenv(shell_t *shell, ll_tree_t *node)
{
    int size = 0;

    for (size = 0; node->argv[size] != NULL; ++size);
    if (size == 1) {
        dprintf(2, "unsetenv: Too few arguments.\n");
        return (1);
    }
    if (strcmp(node->argv[1], "*") == 0) {
        builtin_unsetenv_all(shell);
        return (0);
    }
    for (int i = 1; node->argv[i] != NULL; ++i)
        builtin_unsetenv_change(shell, node->argv[i]);
    return (0);
}

void builtin_env(shell_t *shell)
{
    for (int i = 0; shell->env[i] != NULL; ++i)
        dprintf(2, "%s\n", shell->env[i]);
}