/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** builtin_cd.c
*/

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "execute.h"

static int builtin_cd_errors(char **argv, int size)
{
    DIR *fd = NULL;

    if (size == 1 || strcmp("~", argv[1]) == 0 ||
        strcmp("-", argv[1]) == 0)
        return (0);
    fd = opendir(argv[1]);
    if (fd == NULL) {
        if (access(argv[1], F_OK) == 0) {
            dprintf(2, "%s: Not a directory.\n", argv[1]);
            return (1);
        }
        if (argv[1] != NULL)
            dprintf(2, "%s: No such file or directory.\n", argv[1]);
        return (1);
    }
    closedir(fd);
    return (0);
}

static void builtin_cd_home(char **env)
{
    int i = 0;

    for (i = 0; env[i] != NULL; ++i) {
        if (strncmp("HOME=", env[i], 5) == 0)
            break;
    }
    chdir(env[i] + 5);
}

static void builtin_cd_back(shell_t *shell)
{
    char *last_pwd = strdup(shell->old_pwd);

    free(shell->old_pwd);
    shell->old_pwd = getcwd(NULL, 0);
    chdir(last_pwd);
    free(last_pwd);
}

static int builtin_cd_exec(shell_t *shell, char **env, char **argv,
int size)
{
    if (size == 2 && strcmp("-", argv[1]) == 0) {
        builtin_cd_back(shell);
        return (0);
    }
    free(shell->old_pwd);
    shell->old_pwd = getcwd(NULL, 0);
    if (size == 1 || strcmp("~", argv[1]) == 0) {
        builtin_cd_home(env);
        return (0);
    }
    chdir(argv[1]);
    return (0);
}

int builtin_cd(shell_t *shell, ll_tree_t *node)
{
    int size = 0;

    for (size = 0; node->argv[size] != NULL; ++size);
    if (size > 2) {
        dprintf(2, "cd: Too many arguments.\n");
        return (1);
    }
    if (builtin_cd_errors(node->argv, size))
        return (1);
    builtin_cd_exec(shell, shell->env, node->argv, size);
    return (0);
}