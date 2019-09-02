/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** execution_utils.c
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mysh.h"
#include "execute.h"

void reset_fd(shell_t *shell)
{
    dup2(shell->fd_out, 1);
    dup2(shell->fd_in, 0);
    if (shell->fd_pipe[0] != 1) {
        close(shell->fd_pipe[0]);
        shell->fd_pipe[0] = 1;
    }
    if (shell->fd_pipe[1] != 0) {
        close(shell->fd_pipe[1]);
        shell->fd_pipe[1] = 0;
    }
    if (shell->fd_redirect[0] != 1) {
        close(shell->fd_redirect[0]);
        shell->fd_redirect[0] = 1;
    }
    if (shell->fd_redirect[1] != 0) {
        close(shell->fd_redirect[1]);
        shell->fd_redirect[1] = 0;
    }
}