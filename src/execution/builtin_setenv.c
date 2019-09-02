/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** builtin_setenv.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "execute.h"

char *my_strcat(char *str1, char *str2)
{
    int size = (int)(strlen(str1) + strlen(str2));
    char *result = malloc(sizeof(char) * (size + 2));
    int i = 0;

    if (result == NULL)
        return (NULL);
    for (int u = 0; u < size + 2; ++u)
        result[u] = 0;
    for (int u = 0; str1 && str1[u]; ++u)
        result[i++] = str1[u];
    for (int u = 0; str2 && str2[u]; ++u)
        result[i++] = str2[u];
    return (result);
}

void builtin_setenv_createnew(shell_t *command, char **argv, char *to_find,
int size)
{
    char **new_env = malloc(sizeof(char *) * (size + 2));

    for (int i = 0; i < size + 2; ++i) {
        new_env[i] = NULL;
        if (i < size && command->env[i] != NULL)
            new_env[i] = strdup(command->env[i]);
    }
    if (argv[2] != NULL) {
        new_env[size] = my_strcat(to_find, argv[2]);
    } else
        new_env[size] = strdup(to_find);
    for (int i = 0; command->env[i] != NULL; ++i)
        free(command->env[i]);
    free(command->env);
    command->env = new_env;
}

void builtin_setenv_change(shell_t *shell, char **argv, char *to_find,
int pos)
{
    int size = 0;

    if (pos == -1) {
        for (size = 0; shell->env[size] != NULL; ++size);
        builtin_setenv_createnew(shell, argv, to_find, size);
        return;
    }
    free(shell->env[pos]);
    if (argv[2] != NULL) {
        shell->env[pos] = my_strcat(to_find, argv[2]);
    } else
        shell->env[pos] = strdup(to_find);
}

int checks_setenv(shell_t *shell, ll_tree_t *node)
{
    int size = 0;

    for (size = 0; node->argv[size] != NULL; ++size);
    if (size == 1) {
        builtin_env(shell);
        return (1);
    }
    if (size > 3) {
        dprintf(2, "setenv: Too many arguments.\n");
        return (1);
    }
    for (int i = 0; node->argv[1][i] != '\0'; ++i) {
        if (!((node->argv[1][i] >= 'a' && node->argv[1][i] <= 'z') ||
        (node->argv[1][i] >= 'A' && node->argv[1][i] <= 'Z') ||
        (node->argv[1][i] >= '0' && node->argv[1][i] <= '9'))) {
            dprintf(2, "setenv: Variable name must contain alphanumeric \
characters.\n");
            return (1);
        }
    }
    return (0);
}

int builtin_setenv(shell_t *shell, ll_tree_t *node)
{
    char *to_find = NULL;
    int pos = -1;

    if (checks_setenv(shell, node))
        return (1);
    to_find = my_strcat(node->argv[1], "=");
    for (int i = 0; shell->env[i] != NULL; ++i) {
        if (strncmp(to_find, shell->env[i], strlen(to_find)) == 0) {
            pos = i;
            break;
        }
    }
    builtin_setenv_change(shell, node->argv, to_find, pos);
    free(to_find);
    return (0);
}
