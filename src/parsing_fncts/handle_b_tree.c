/*
** EPITECH PROJECT, 2018
** handle_b_tree.c
** File description:
** handle b tree
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"

int add_node(tree_t **node, bool left, int type)
{
    tree_t *new_node = malloc(sizeof(tree_t));

    if (!new_node)
        return (84);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    new_node->ope = type;
    if (!*node) {
        *node = new_node;
        return (0);
    }
    if (left)
        (*node)->left = new_node;
    else
        (*node)->right = new_node;
    return (0);
}

tree_t *get_sidest_node(tree_t *root, bool left)
{
    tree_t *tmp = root;

    if (left) {
        while (tmp->left != NULL)
            tmp = tmp->left;
        return (tmp);
    } else {
        while (tmp->right != NULL)
            tmp = tmp->right;
        return (tmp);
    }
    return (NULL);
}

int free_tree(tree_t *tree)
{
    tree_t *tmp = NULL;

    while (tree != NULL) {
        tmp = tree;
        if (tree->right != NULL) {
            free(tree->left->data);
            free(tree->left);
        }
        tree = tree->right;
        free(tmp->data);
        free(tmp);
    }
    return (0);
}
