/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** handling_double_left.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysh.h"
#include "execute.h"

int redirection_check(ll_tree_t *tree)
{
    if (tree != NULL)
        return (0);
    dprintf(2, "Missing name for redirect.\n");
    return (1);
}

ll_tree_t *d_left_add_node(ll_tree_t *tree, char *string)
{
    ll_tree_t *pipe_node = create_node(LL_PIPE);
    ll_tree_t *string_node = create_node(LL_COM);

    if (string[strlen(string) - 1] == '\n')
        string[strlen(string) - 1] = '\0';
    string_node->argv = malloc(sizeof(char *) * 3);
    string_node->argv[0] = strdup("echo");
    string_node->argv[1] = strdup(string);
    string_node->argv[2] = NULL;
    pipe_node->left = string_node;
    pipe_node->right = tree->left;
    return (pipe_node);
}

int my_dleft_strcmp(const char *str1, const char *str2)
{
    int i = 0;

    for (i = 0; str1 && str1[i]; ++i) {
        if (str1[i] != str2[i])
            return (1);
    }
    if (str2[i + 1] != '\0')
        return (1);
    return (0);
}

int handle_d_left(ll_tree_t *tree, shell_t *shell)
{
    char *buffer = NULL;
    char *string = malloc(sizeof(char) * 1);
    size_t n = 0;
    int bytes = 0;

    string[0] = '\0';
    while (1) {
        printf("? ");
        bytes = getline(&buffer, &n, stdin);
        if (bytes == -1 || bytes == 0 || buffer[0] == '\0')
            break;
        if (my_dleft_strcmp(tree->right->argv[0], buffer) == 0)
            break;
        string = realloc(string, strlen(string) + strlen(buffer) + 1);
        strcat(string, buffer);
        free(buffer);
        buffer = NULL;
    }
    handle_pipe(d_left_add_node(tree, string), shell);
    return (0);
}