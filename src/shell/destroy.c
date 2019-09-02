/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** destroy.c
*/

#include <stdlib.h>
#include "ll_parser.h"

void destroy_string_array(char **array)
{
    for (int i = 0; array && array[i] != NULL; ++i) {
        free(array[i]);
    }
    free(array);
}

void destroy_ll_tree(ll_tree_t *ll_tree)
{
    if (ll_tree == NULL)
        return;
    if (ll_tree->argv != NULL) {
        for (int i = 0; ll_tree->argv[i] != NULL; ++i)
            free(ll_tree->argv[i]);
        free(ll_tree->argv);
    }
    if (ll_tree->left != NULL)
        destroy_ll_tree(ll_tree->left);
    if (ll_tree->right != NULL)
        destroy_ll_tree(ll_tree->right);
    free(ll_tree);
}