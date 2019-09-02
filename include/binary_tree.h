/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** binary_tree.h
*/

#ifndef PSU_42SH_2017_BINARY_TREE_H
#define PSU_42SH_2017_BINARY_TREE_H

#include <stdbool.h>

typedef struct tree_b {
    int ope;
    char **data;
    struct tree_b *left;
    struct tree_b *right;
    struct tree_b *parent;
} tree_t;

/*
* ##########################################################
* #                      FUNCTIONS                         #
* ##########################################################
*/

int add_node(tree_t **node, bool left, int type);
tree_t *get_sidest_node(tree_t *root, bool left);
int free_tree(tree_t *tree);

#endif //PSU_42SH_2017_BINARY_TREE_H
