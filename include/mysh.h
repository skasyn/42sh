/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** mysh.h
*/

#ifndef PSU_42SH_2017_MYSH_H
#define PSU_42SH_2017_MYSH_H

#include "ll_parser.h"
#define MAX_READ_LINE 2048

typedef struct l_list_s {
    char *new;
    char *old;
    struct l_list_s *prev;
    struct l_list_s *next;
} l_list_t;

typedef struct shell_s {
    ll_struct_t *llstruct;
    char *old_pwd;
    char **env;
    char **path;
    char *path_str;
    int end;
    int stop_exec;
    int fd_in;
    int fd_out;
    int fd_redirect[2];
    int fd_pipe[2];
    int return_value;
    l_list_t *aliases;
} shell_t;

int exec_node(shell_t *shell, ll_tree_t *tree);
int check_if_remplace_aliases(char *str, l_list_t *list);
shell_t *create_shell(char **env);
void read_loop(shell_t *shell);
char **get_right_params(char *buffer);
void redirect_all_std(void);
void set_tty_non_canon(void);
char *put_aliases(char *str, l_list_t *list);
void show_prompt(void);


#endif //PSU_42SH_2017_MYSH_H
