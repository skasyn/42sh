/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** file_command.c
*/

#include <stdlib.h>
#include <string.h>
#include "ll_parser.h"
#include "parsing.h"

void remove_last_return(char **array)
{
    int i = 0;
    int u = 0;

    for (i = 0; array[i] != NULL; ++i);
    i--;
    for (u = 0; array[i][u] != '\0'; ++u);
    u--;
    if (u != -1 && i != -1 && array[i][u] == '\n')
        array[i][u] = '\0';
}

bool ll_file(ll_tree_t **tree, ll_struct_t *llstruct)
{
    ll_tree_t *node = create_node(LL_FILE);

    if (ll_word(llstruct)) {
        if (llstruct->array[llstruct->i] == NULL)
            return (false);
        node->argv = malloc(sizeof(char *) * 2);
        node->argv[0] = strdup(llstruct->array[llstruct->i]);
        node->argv[1] = NULL;
        remove_last_return(node->argv);
        llstruct->i++;
        *tree = node;
        return (true);
    }
    free_node(node);
    return (false);
}

bool ll_command(ll_tree_t **tree, ll_struct_t *llstruct)
{
    ll_tree_t *node = create_node(LL_COM);

    if (ll_word(llstruct)) {
        node->argv = concat_com(llstruct->array, &llstruct->i);
        remove_last_return(node->argv);
        *tree = node;
        return (true);
    }
    free_node(node);
    return (false);
}
