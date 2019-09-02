/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** handling_operators.c
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "execute.h"
#include "mysh.h"

int find_slash(const char *str)
{
    for (int i = 0; str && str[i] != '\0'; ++i) {
        if (str[i] == '/')
            return (1);
    }
    return (0);
}

int exec_forks(ll_tree_t *node, shell_t *shell, int is_path)
{
    int status = 0;

    if (fork() == 0) {
        if (is_path)
            status = execve(node->argv[0], node->argv, shell->env);
        else
            status = execvpe(node->argv[0], node->argv, shell->env);
    } else
        wait(&shell->return_value);
    return (status);
}

int handle_com(ll_tree_t *node, shell_t *shell)
{
    int is_path = find_slash(node->argv[0]);
    int status = 0;

    if (!check_builtins(shell, node)) {
        status = exec_forks(node, shell, is_path);
        check_signal(shell->return_value, node->argv[0], status);
        if (status == -1) {
            shell->return_value = -1;
            exit(-1);
        }
    }
    return (shell->return_value);
}

int handle_and(ll_tree_t *node, shell_t *shell)
{
    if (!exec_node(shell, node->left))
        exec_node(shell, node->right);
    return (0);
}

int handle_or(ll_tree_t *node, shell_t *shell)
{
    if (exec_node(shell, node->left))
        exec_node(shell, node->right);
    return (0);
}

int handle_pipe(ll_tree_t *node, shell_t *shell)
{
    int status = 0;

    pipe(shell->fd_pipe);
    if (fork() == 0) {
        close(shell->fd_pipe[0]);
        dup2(shell->fd_pipe[1], 1);
        close(shell->fd_pipe[1]);
        status = exec_node(shell, node->left);
        exit(shell->return_value);
    } else {
        close(shell->fd_pipe[1]);
        dup2(shell->fd_pipe[0], 0);
        close(shell->fd_pipe[0]);
        exec_node(shell, node->right);
        wait(&shell->return_value);
    }
    check_signal(shell->return_value, "", status);
    reset_fd(shell);
    return (shell->return_value);
}

int handle_file(ll_tree_t *node, shell_t *shell)
{
    (void)node;
    (void)shell;
    return (0);
}