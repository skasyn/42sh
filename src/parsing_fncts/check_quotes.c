/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** check_quotes.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_escaped(const char *str, int i, char c)
{
    if (i == 0) {
        if (str[i] == c)
            return (true);
        else
            return (false);
    } else {
        if (str[i] == c && str[i - 1] != '\\')
            return (true);
        else
            return (false);
    }
}

static bool single_quotes(const char *str, int *index)
{
    int i = *index;

    while ((is_escaped(str, i, '\'') == false) && str[i])
        ++i;
    if (str[i] == '\0') {
        dprintf(2, "Unmatched '\''.\n");
        return (false);
    }
    *index = i + 1;
    return (true);
}

static bool double_quotes(const char *str, int *index)
{
    int i = *index;

    while (is_escaped(str, i, '\"') == false && str[i])
        ++i;
    if (str[i] == '\0') {
        dprintf(2, "Unmatched '\"'.\n");
        return (false);
    }
    *index = i + 1;
    return (true);
}

static bool handle_quotes(const char *str, int *index)
{
    if (is_escaped(str, *index, '\'') == true) {
        ++*index;
        if (single_quotes(str, index))
            return (true);
        else
            return (false);
    } else if (is_escaped(str, *index, '\"') == true) {
        ++*index;
        if (double_quotes(str, index))
            return (true);
        else
            return (false);
    }
    ++*index;
    return (true);
}

bool check_quotes(char *str)
{
    int i = 0;
    bool car = false;

    if (str == NULL)
        return (false);
    for (int j = 0; str[j]; ++j)
        if (str[j] != '\t' && str[j] != ' ')
            car = true;
    if (car == false)
        return (false);
    while (str[i]) {
        if (handle_quotes(str, &i) == false) {
            free(str);
            return (false);
        }
    }
    return (true);
}