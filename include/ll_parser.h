/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** ll_parser.h
*/

#ifndef PSU_42SH_2017_LL_PARSER_H
#define PSU_42SH_2017_LL_PARSER_H

#include <stdbool.h>

enum {ROOT = -1, LL_COM, LL_AND, LL_OR, LL_PIPE, LL_LEFT,
    LL_DOUBLE_LEFT, LL_RIGHT, LL_DOUBLE_RIGHT, LL_SEMI, LL_FILE};

#define OPE_AND "&&"
#define OPE_OR "||"
#define OPE_PIPE "|"
#define OPE_S_LEFT "<"
#define OPE_D_LEFT "<<"
#define OPE_S_RIGHT ">"
#define OPE_D_RIGHT ">>"
#define OPE_SEMI ";"

typedef struct ll_tree_s {
    int type;
    char **argv;
    struct ll_tree_s *left;
    struct ll_tree_s *right;
} ll_tree_t;

typedef struct ll_struct_s {
    char **array;
    int i;
    ll_tree_t *ll_tree;
} ll_struct_t;

ll_tree_t *create_node(int type);
void free_node(ll_tree_t *node);

ll_tree_t *ll_exp(ll_struct_t *llstruct);
bool ll_semi(ll_tree_t **tree, ll_struct_t *llstruct);
bool ll_or_exp(ll_tree_t **tree, ll_struct_t *llstruct);
bool ll_and_exp(ll_tree_t **tree, ll_struct_t *llstruct);
bool ll_pipe_exp(ll_tree_t **tree, ll_struct_t *llstruct);
bool ll_redir_exp(ll_tree_t **tree, ll_struct_t *llstruct);
bool ll_redir_standard_left(ll_tree_t **tree, ll_struct_t *llstruct);
bool ll_redir_special_left(ll_tree_t **tree, ll_struct_t *llstruct);
bool ll_redir_standard_right(ll_tree_t **tree, ll_struct_t *llstruct);
bool ll_redir_special_right(ll_tree_t **tree, ll_struct_t *llstruct);
bool ll_command(ll_tree_t **tree, ll_struct_t *llstruct);
bool ll_file(ll_tree_t **tree, ll_struct_t *llstruct);
bool ll_word(ll_struct_t *llstruct);
bool ll_read_right(ll_struct_t *llstruct);
bool ll_read_left(ll_struct_t *llstruct);
bool ll_read_token(ll_struct_t *llstruct, char *str);
bool ll_redir_right(ll_tree_t **tree, ll_struct_t *llstruct);

#endif //PSU_42SH_2017_LL_PARSER_H
