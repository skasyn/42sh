/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** concat_com.c
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "parsing.h"

bool is_a_separator(const char *str)
{
    for (int i = 0; separators[i]; ++i)
        if (!strcmp(str, separators[i]))
            return (true);
    return (false);
}

static int count_words(char **params, int *index)
{
    int i = *index;
    int size = 0;

    while (params[i] && !is_a_separator(params[i])) {
        ++i;
        ++size;
    }
    return (size);
}

char **concat_com(char **params, int *index)
{
    int size = 0;
    int i = 0;
    char **new_params = NULL;

    if (params[*index] == NULL)
        return (NULL);
    size = count_words(params, index);
    new_params = malloc(sizeof(char *) * (size + 1));
    if (!new_params)
        return (NULL);
    while (params[*index] && !is_a_separator(params[*index])) {
        new_params[i] = strdup(params[*index]);
        if (!new_params[i])
            return (NULL);
        ++i;
        ++*index;
    }
    new_params[i] = NULL;
    return (new_params);
}