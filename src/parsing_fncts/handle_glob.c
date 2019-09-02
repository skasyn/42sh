/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** handle_glob.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <glob.h>
#include <string.h>

static bool is_a_global(const char *params)
{
    for (int i = 0; params[i]; ++i) {
        if (params[i] == '*')
            return (true);
        else if (params[i] == '?')
            return (true);
    }
    return (false);
}

static void handle_params(char **param, glob_t *globbuf, bool *tmp, int i)
{
    if (is_a_global(param[i]) && i != 0 && (strcmp("unsetenv", param[i - 1])
    != 0) && (strcmp("setenv", param[i - 1]) != 0)) {
        if (*tmp == false) {
            glob(param[i], GLOB_DOOFFS, NULL, globbuf);
            *tmp = true;
        } else
            glob(param[i], GLOB_DOOFFS | GLOB_APPEND, NULL, globbuf);
    }
}

static size_t get_size(char **params)
{
    size_t size = 0;
    bool is_format = false;

    if (!params || !params[0])
        return (0);
    for (int i = 0; params[i]; ++i) {
        if (!is_a_global(params[i]))
            ++size;
        else if (i != 0 && strcmp("unsetenv", params[i - 1]) != 0 &&
            (strcmp("setenv", params[i - 1]) != 0))
            is_format = true;
    }
    if (!is_format)
        return (0);
    return (size);
}

char **handle_glob(char **params)
{
    int j = 0;
    glob_t globbuf;
    size_t size = 0;
    bool tmp = false;

    if ((size = get_size(params)) == 0)
        return (NULL);
    globbuf.gl_offs = size;
    for (int i = 0; params[i]; ++i)
        handle_params(params, &globbuf, &tmp, i);
    for (int i = 0; params[i]; ++i) {
        if (!is_a_global(params[i])) {
            globbuf.gl_pathv[j] = strdup(params[i]);
            ++j;
        }
    }
    return (&globbuf.gl_pathv[0]);
}