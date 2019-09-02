/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** init.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mysh.h"

char **get_path(shell_t *shell)
{
    char **path = NULL;
    char *path_env = getenv("PATH");
    int size = 2;

    if (path_env == NULL) {
        path = malloc(sizeof(char *));
        path[0] = NULL;
        return (path);
    }
    for (int i = 0; path_env[i] != '\0'; ++i) {
        if (path_env[i] == ':')
            size++;
    }
    shell->path_str = strdup(path_env);
    path = malloc(sizeof(char *) * size);
    path[0] = strtok(shell->path_str + 5, ":");
    for (int i = 1; path[i - 1] != NULL; ++i)
        path[i] = strtok(NULL, ":");
    return (path);
}

void get_env(char *const *env, shell_t *shell)
{
    int env_size = 1;

    for (int i = 0; env[i] != NULL; ++i)
        env_size++;
    if (env_size > 1) {
        shell->path_str = NULL;
        shell->env = malloc(sizeof(char *) * env_size);
        for (env_size = 0; env[env_size] != NULL; ++env_size)
            shell->env[env_size] = strdup(env[env_size]);
        shell->path = get_path(shell);
        shell->env[env_size] = NULL;
    } else {
        shell->env = malloc(sizeof(char *) * 1);
        shell->env[0] = NULL;
        shell->path = malloc(sizeof(char *) * 1);
        shell->path[0] = NULL;
    }
}

shell_t *create_shell(char **env)
{
    shell_t *shell = malloc(sizeof(shell_t));

    if (shell == NULL)
        return (NULL);
    shell->llstruct = malloc(sizeof(ll_struct_t));
    if (shell->llstruct == NULL)
        return (NULL);
    get_env(env, shell);
    shell->fd_in = dup(0);
    shell->fd_out = dup(1);
    shell->fd_pipe[0] = 1;
    shell->fd_pipe[1] = 0;
    shell->fd_redirect[0] = 1;
    shell->fd_redirect[1] = 0;
    shell->old_pwd = getcwd(NULL, 0);
    shell->end = 0;
    shell->stop_exec = 0;
    shell->aliases = NULL;
    shell->return_value = 0;
    shell->llstruct->ll_tree = NULL;
    return (shell);
}