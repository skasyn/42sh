/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** move_params.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parsing.h"

static bool check_redir(char *params)
{
    char *redir[] = {
        "<",
        ">",
        "<<",
        ">>",
        NULL
    };

    for (int i = 0; redir[i]; ++i)
        if (!strcmp(redir[i], params))
            return (true);
    return (false);
}

static void move_them(char **params, int *i)
{
    char *redir = params[*i];
    char *to = NULL;
    int j = *i + 2;

    if (params[*i + 1] == NULL)
        return;
    to = params[*i + 1];
    for (; params[j]; ++j) {
        if (is_a_separator(params[j]))
            break;
        else {
            params[*i] = params[j];
            ++*i;
        }
    }
    params[j - 2] = redir;
    params[j - 1] = to;
}

void clean_n(char *str)
{
    for (int i = 0; str[i]; ++i)
        if (str[i] == '\n')
            str[i] = '\0';
}

void move_params(char **params)
{
    for (int i = 0; params[i]; ++i) {
        if (check_redir(params[i])) {
            move_them(params, &i);
        }
        clean_n(params[i]);
    }
}
