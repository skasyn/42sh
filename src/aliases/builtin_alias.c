/*
** EPITECH PROJECT, 2018
** builtin_alias
** File description:
** builtin
*/

#include "execute.h"
#include "mysh.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void print_parenthesis(char *str1, char *str2)
{
    for (int i = 0; str2[i]; i++) {
        if (str2[i] == ' ') {
            printf("%s (%s)\n", str1, str2);
            return;
        }
    }
    printf("%s %s\n", str1, str2);
}

static int check_if_new_exist(shell_t *shell, char *str1, char *str2)
{
	l_list_t *tmp = shell->aliases;

    for (; tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->new, str1) == 0) {
            tmp->old = \
            strcpy(tmp->old, str2);
            free(str1);
            free(str2);
            return (0);
        }
    }
    return (1);
}

static char *get_str_from_arr(char **argv)
{
    int i = 0;
    int k = 0;
    char *str = NULL;

    for (i = 2; argv[i]; i++)
        k = k + strlen(argv[i]);
    str =  malloc(sizeof(char) * (k + i));
    if (str == NULL)
        exit(84);
    k = 0;
    for (i = 2; argv[i]; i++) {
        for (int j = 0; argv[i][j]; j++) {
            str[k] = argv[i][j];
            k++;
        }
        if (argv[i + 1] != NULL)
            str[k] = ' ';
        k++;
    }
    str[k -1] = '\0';
    return (str);
}

static void builtin_exec_alias(shell_t *shell, ll_tree_t *node)
{
    char *new = NULL;
    char *old = NULL;

    new = malloc(sizeof(char) * (strlen(node->argv[1]) + 1));
    if (new == NULL)
        exit(84);
    new = strcpy(new, node->argv[1]);
    if (get_arrlen(node->argv) == 3) {
        old = malloc(sizeof(char) * (strlen(node->argv[2]) + 1));
        if (old == NULL)
            exit(84);
        old = strcpy(old, node->argv[2]);
    } else
        old = get_str_from_arr(node->argv);
    if (check_if_new_exist(shell, new, old) == 0)
        return;
    if (shell->aliases == NULL)
        shell->aliases = init_list(old, new);
    else
        new_node(shell->aliases, old, new);
}

int builtin_alias(shell_t *shell, ll_tree_t *node)
{
    l_list_t *tmp = shell->aliases;

    if (get_arrlen(node->argv) == 1) {
        for (; tmp != NULL; tmp = tmp->next)
            print_parenthesis(tmp->new, tmp->old);
        return (0);
    }
    if (get_arrlen(node->argv) == 2) {
        for (; tmp != NULL
        && strcmp(tmp->new, node->argv[1])
        != 0; tmp = tmp->next);
        if (tmp == NULL)
            return (0);
        printf("%s\n", tmp->old);
        return (0);
    }
    builtin_exec_alias(shell, node);
    return (0);
}
