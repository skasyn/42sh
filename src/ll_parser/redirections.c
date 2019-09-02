/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** redirections.c
*/

#include <stdlib.h>
#include <string.h>
#include "ll_parser.h"

bool ll_redir_special_right(ll_tree_t **tree, ll_struct_t *llstruct)
{
    ll_tree_t *node = create_node(LL_RIGHT);

    if (llstruct->array[llstruct->i] != NULL &&
        strcmp(llstruct->array[llstruct->i], ">>") == 0)
        node->type = LL_DOUBLE_RIGHT;
    if (ll_read_right(llstruct)) {
        if (ll_file(&node->left, llstruct))
            ll_command(&node->right, llstruct);
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

bool ll_redir_standard_right(ll_tree_t **tree, ll_struct_t *llstruct)
{
    ll_tree_t *node = create_node(LL_RIGHT);

    if (ll_command(&node->left, llstruct)) {
        if (llstruct->array[llstruct->i] != NULL &&
            strcmp(llstruct->array[llstruct->i], ">>") == 0)
            node->type = LL_DOUBLE_RIGHT;
        if (ll_read_right(llstruct))
            ll_file(&node->right, llstruct);
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

bool ll_redir_right(ll_tree_t **tree, ll_struct_t *llstruct)
{
    if (ll_redir_standard_right(tree, llstruct)
        || ll_redir_special_right(tree, llstruct))
        return (true);
    return (false);
}

bool ll_redir_special_left(ll_tree_t **tree, ll_struct_t *llstruct)
{
    ll_tree_t *node = create_node(LL_LEFT);

    if (llstruct->array[llstruct->i] != NULL &&
        strcmp(llstruct->array[llstruct->i], "<<") == 0)
        node->type = LL_DOUBLE_LEFT;
    if (ll_read_left(llstruct)) {
        if (ll_file(&node->left, llstruct))
            ll_redir_exp(&node->right, llstruct);
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

bool ll_redir_standard_left(ll_tree_t **tree, ll_struct_t *llstruct)
{
    ll_tree_t *node = create_node(LL_LEFT);

    if (ll_redir_right(&node->left, llstruct)) {
        if (llstruct->array[llstruct->i] != NULL &&
            strcmp(llstruct->array[llstruct->i], "<<") == 0)
            node->type = LL_DOUBLE_LEFT;
        if (ll_read_left(llstruct))
            ll_redir_exp(&node->right, llstruct);
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
