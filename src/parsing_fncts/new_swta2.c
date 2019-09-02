/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** swta
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <parsing.h>
#include "string.h"

bool check_char(const char *str, int i, char c)
{
    if (str[i] == c) {
        if (i != 0 && str[i - 1] != '\\')
            return (true);
        else if (i == 0)
            return (true);
        else
            return (false);
    }
    return (false);
}

static void handle_word(const char *str, int *i)
{
    if (check_char(str, *i, '\"')) {
        ++*i;
        for (; str[*i] && !check_char(str, *i, '\"') && str[*i] != '\n'; ++*i);
        if (str[*i] != '\0')
            ++*i;
        return;
    } else if (check_char(str, *i, '\'')) {
        ++*i;
        for (; str[*i] && !check_char(str, *i, '\'') && str[*i] != '\n'; ++*i);
        if (str[*i] != '\0')
            ++*i;
        return;
    } else {
        for (; str[*i] && (str[*i] != ' ' && str[*i] != '\t'); ++*i);
        return;
    }
}

static int get_nbr_words(const char *str)
{
    int words = 0;

    for (int i = 0; str[i] && str[i] != '\n';) {
        for (; str[i] && (str[i] == ' ' || str[i] == '\t'); ++i);
        handle_word(str, &i);
        for (; str[i] && (str[i] == ' ' || str[i] == '\t'); ++i);
        ++words;
    }
    return (words);
}

char **default_output(void)
{
    char **def = NULL;

    def = malloc(sizeof(char *) * 2);
    if (!def)
        return (NULL);
    def[0] = strdup("\n");
    if (!def[0])
        return (NULL);
    def[1] = NULL;
    return (def);
}

char **stwa(const char *str)
{
    int size = get_nbr_words(str);
    char **test = NULL;
    int j = 0;

    if (size == 0)
        return (default_output());
    test = malloc(sizeof(char *) * (size + 1));
    if (!test)
        return (NULL);
    for (int i = 0; i < size; ++i) {
        test[i] = get_word(str, &j);
        if (!test[i])
            return (NULL);
    }
    test[size] = NULL;
    return (test);
}