/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** get_exp.c
*/

#include <stdlib.h>
#include "mysh.h"
#include "ll_parser.h"

ll_tree_t *ll_exp(ll_struct_t *llstruct)
{
    ll_tree_t *tree = create_node(ROOT);

    if (ll_or_exp(&tree->left, llstruct)) {
        if (ll_read_token(llstruct, OPE_SEMI))
            ll_semi(&tree->right, llstruct);
        return (tree);
    }
    free_node(tree);
    return (NULL);
}