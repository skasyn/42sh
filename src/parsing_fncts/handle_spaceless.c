/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** handle_spaceless.c
*/

#include <stdlib.h>
#include <stdbool.h>

static bool is_a_separator(const char c)
{
    char separators[] = {
        '>',
        '<',
        '|',
        ';'
    };

    for (int i = 0; separators[i]; ++i)
        if (c == separators[i])
            return (true);
    return (false);
}

static int count_space_needed(char *str)
{
    int size = 0;

    for (int i = 0; str[i]; ++i) {
        if (i != 0 && is_a_separator(str[i]) && (str[i - 1] != ' ' ||
            str[i + 1] != ' '))
            size += 2;
        else if (is_a_separator(str[i]) && str[i + 1] != ' ')
            ++size;
        ++size;
    }
    return (size);
}

static void handle_it(const char *str, char *new, int *i, int *j)
{
    if (*i != 0 && !is_a_separator(str[*i - 1])) {
        new[*j] = ' ';
        ++*j;
    }
    new[*j] = str[*i];
    ++*j;
    ++*i;
    if (is_a_separator(str[*i])) {
        new[*j] = str[*i];
        ++*j;
        new[*j] = ' ';
        ++*j;
        ++*i;
    } else {
        new[*j] = ' ';
        ++*j;
    }
}

static void fill_spaceless(const char *str, char *new)
{
    int i = 0;
    int j = 0;

    while (str[i]) {
        if (i != 0 && is_a_separator(str[i]) && (str[i - 1] != ' ' ||
            str[i + 1] != ' '))
            handle_it(str, new, &i, &j);
        else if (i == 0 && is_a_separator(str[i]) && str[i + 1] != ' ')
            handle_it(str, new, &i, &j);
        else {
            new[j] = str[i];
            ++i;
            ++j;
        }
    }
    new[j] = '\0';
}

char *handle_spaceless(char *str)
{
    int size = 0;
    char *new = NULL;

    if (!str || str[0] == '\n')
        return (NULL);
    size = count_space_needed(str);
    new = malloc(sizeof(char) * (size + 1));
    if (!new)
        return (NULL);
    fill_spaceless(str, new);
    return (new);
}