/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** main
*/

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include "execute.h"
#include "parsing.h"
#include "ll_parser.h"
#include "mysh.h"
#include "destroy.h"

void destroy_shell_struct(shell_t *shell)
{
    l_list_t *destroying_list;
    l_list_t *buffer;

    for (destroying_list = shell->aliases; destroying_list != NULL;
    destroying_list = buffer) {
        buffer = destroying_list->next;
        free(destroying_list->old);
        free(destroying_list->new);
        free(destroying_list);
    }
    for (int i = 0; shell->env[i] != NULL; ++i)
        free(shell->env[i]);
    free(shell->env);
    free(shell->path);
    free(shell->path_str);
    free(shell->llstruct);
    free(shell->old_pwd);
    free(shell);

}

int main(int argc, char **argv, char **env)
{
    shell_t *shell = create_shell(env);

    (void)argc;
    (void)argv;
    signal(SIGINT, sigint_signal);
    read_loop(shell);
    destroy_shell_struct(shell);
    return (0);
}
