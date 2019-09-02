/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** handling_redirect.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "execute.h"
#include "mysh.h"

int handle_left(ll_tree_t * tree, shell_t *shell)
{
    int errnum = 0;

    if (redirection_check(tree->left))
        return (1);
    shell->fd_redirect[1] = open(tree->right->argv[0], O_RDONLY);
    errnum = errno;
    if (shell->fd_redirect[1] == -1) {
        dprintf(2, "%s: %s.\n", tree->right->argv[0], strerror(errnum));
        shell->fd_redirect[1] = 0;
        shell->stop_exec = 1;
        return (1);
    }
    dup2(shell->fd_redirect[1], 0);
    exec_node(shell, tree->left);
    reset_fd(shell);
    return (0);
}

int handle_right(ll_tree_t *tree, shell_t *shell)
{
    int errnum = 0;

    if (redirection_check(tree->left))
        return (1);
    shell->fd_redirect[0] = open(tree->right->argv[0],
    O_RDWR | O_TRUNC | O_CREAT, 0664);
    errnum = errno;
    if (shell->fd_redirect[0] == -1) {
        dprintf(2, "%s: %s.\n", tree->right->argv[0], strerror(errnum));
        shell->fd_redirect[0] = 1;
        shell->stop_exec = 1;
        return (1);
    }
    dup2(shell->fd_redirect[0], 1);
    exec_node(shell, tree->left);
    reset_fd(shell);
    return (0);
}

int handle_d_right(ll_tree_t *tree, shell_t *shell)
{
    int errnum = 0;

    if (redirection_check(tree->left))
        return (1);
    shell->fd_redirect[0] = open(tree->right->argv[0],
    O_RDWR | O_APPEND | O_CREAT, 0664);
    errnum = errno;
    if (shell->fd_redirect[0] == -1) {
        dprintf(2, "%s: %s.\n", tree->right->argv[0], strerror(errnum));
        shell->fd_redirect[0] = 1;
        shell->stop_exec = 1;
        return (1);
    }
    dup2(shell->fd_redirect[0], 1);
    exec_node(shell, tree->left);
    reset_fd(shell);
    return (0);
}

int handle_semi(ll_tree_t *tree, shell_t *shell)
{
    exec_node(shell, tree->left);
    exec_node(shell, tree->right);
    return (0);
}