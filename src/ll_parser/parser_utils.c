/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** parser_utils.c
*/

#include <stdlib.h>
#include "ll_parser.h"

ll_tree_t *create_node(int type)
{
    ll_tree_t *node = malloc(sizeof(ll_tree_t));

    if (!node)
        return (NULL);
    node->type = type;
    node->argv = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

void free_node(ll_tree_t *node)
{
    for (int i = 0; node->argv && node->argv[i] != NULL; ++i)
        free(node->argv[i]);
    free(node->argv);
    free(node);
}
