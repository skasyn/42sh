/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** execute.h
*/

#ifndef PSU_42SH_2017_EXECUTE_H
#define PSU_42SH_2017_EXECUTE_H

#include "ll_parser.h"
#include "mysh.h"

extern int (*handle_fnct[]) (ll_tree_t *, shell_t *);

/*
* ##########################################################
* #                      FUNCTIONS                         #
* ##########################################################
*/

// handling_operators.c
int handle_com(ll_tree_t *tree, shell_t *shell);
int handle_and(ll_tree_t *tree, shell_t *shell);
int handle_or(ll_tree_t *tree, shell_t *shell);
int handle_pipe(ll_tree_t *tree, shell_t *shell);
int handle_file(ll_tree_t *tree, shell_t *shell);

// handling_redirect.c
int handle_left(ll_tree_t *tree, shell_t *shell);
int handle_d_left(ll_tree_t *tree, shell_t *shell);
int handle_right(ll_tree_t *tree, shell_t *shell);
int handle_d_right(ll_tree_t *tree, shell_t *shell);
int handle_semi(ll_tree_t *tree, shell_t *shell);

int redirection_check(ll_tree_t *tree);
// builtins

#define BUILTINS_NB 5

typedef struct builtins_s {
    char *str;
    int (*function)(shell_t *shell, ll_tree_t *node);
} builtin_t;

int get_arrlen(char **arr);
char *put_aliasenews(char *str, l_list_t *list);
l_list_t *init_list(char *old, char *new);
void new_node(l_list_t *list, char *old, char *new);
int builtin_alias(shell_t *shell, ll_tree_t *node);
int check_builtins(shell_t *shell, ll_tree_t *node);
int builtin_cd(shell_t *shell, ll_tree_t *node);
int builtin_unsetenv(shell_t *shell, ll_tree_t *node);
int builtin_setenv(shell_t *shell, ll_tree_t *node);
int builtin_exit(shell_t *shell, ll_tree_t *node);
void builtin_env(shell_t *shell);

static const builtin_t builtins[BUILTINS_NB] = {
    {"cd", builtin_cd},
    {"unsetenv", builtin_unsetenv},
    {"setenv", builtin_setenv},
    {"exit", builtin_exit},
    {"alias", builtin_alias}
};

// other
void reset_fd(shell_t *shell);
void check_signal(int sig, char *str, int status);
void sigint_signal(int signum);
char *my_strcat(char *str1, char *str2);
char *access_cmd(char *str, char **path);

#endif //PSU_42SH_2017_EXECUTE_H
