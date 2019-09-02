/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** big_nodes.c
*/

#include <stdlib.h>
#include "ll_parser.h"

bool ll_redir_exp(ll_tree_t **tree, ll_struct_t *llstruct)
{
    if (ll_redir_standard_left(tree, llstruct)
        || ll_redir_special_left(tree, llstruct))
        return (true);
    return (false);
}

bool ll_pipe_exp(ll_tree_t **tree, ll_struct_t *llstruct)
{
    ll_tree_t *node = create_node(LL_PIPE);

    if (ll_redir_exp(&node->left, llstruct)) {
        if (ll_read_token(llstruct, OPE_PIPE))
            ll_pipe_exp(&node->right, llstruct);
        if (node->right == NULL) {
            *tree = node->left;
            free_node(node);
        } else
            *tree = node;
        return (true);
    }
    free_node(node);
    return (false);
}

bool ll_and_exp(ll_tree_t **tree, ll_struct_t *llstruct)
{
    ll_tree_t *node = create_node(LL_AND);

    if (ll_pipe_exp(&node->left, llstruct)) {
        if (ll_read_token(llstruct, OPE_AND))
            ll_and_exp(&node->right, llstruct);
        if (node->right == NULL) {
            *tree = node->left;
            free_node(node);
        } else
            *tree = node;
        return (true);
    }
    free_node(node);
    return (false);
}

bool ll_or_exp(ll_tree_t **tree, ll_struct_t *llstruct)
{
    ll_tree_t *node = create_node(LL_OR);

    if (ll_and_exp(&node->left, llstruct)) {
        if (ll_read_token(llstruct, OPE_OR))
            ll_or_exp(&node->right, llstruct);
        if (node->right == NULL) {
            *tree = node->left;
            free_node(node);
        } else
            *tree = node;
        return (true);
    }
    free_node(node);
    return (false);
}

bool ll_semi(ll_tree_t **tree, ll_struct_t *llstruct)
{
    ll_tree_t *node = create_node(LL_SEMI);

    if (ll_or_exp(&node->left, llstruct)) {
        if (ll_read_token(llstruct, OPE_SEMI))
            ll_semi(&node->right, llstruct);
        if (node->right == NULL) {
            *tree = node->left;
            free_node(node);
        } else
            *tree = node;
        return (true);
    }
    free_node(node);
    return (false);
}