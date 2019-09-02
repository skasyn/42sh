/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** get_word_swta.c
*/

#include <stdlib.h>
#include "parsing.h"

static void copy_it(const char *str, char *word, int *i, char c)
{
    int j = 0;

    ++*i;
    for (; str[*i] && !check_char(str, *i, c) && str[*i] != '\n';
        ++*i, ++j)
        word[j] = str[*i];
    word[j] = '\0';
    if (str[*i] != '\0')
        ++*i;
}

static int get_size_word(const char *str, int i)
{
    int size = 0;

    if (check_char(str, i, '\"')) {
        ++i;
        for (; str[i] && !check_char(str, i, '\"') && str[i] != '\n'; ++i)
            ++size;
        return (size);
    } else if (check_char(str, i, '\'')) {
        ++i;
        for (; str[i] && !check_char(str, i, '\'') && str[i] != '\n'; ++i)
            ++size;
        return (size);
    } else {
        for (; str[i] && (str[i] != ' ' && str[i] != '\t'); ++i)
            ++size;
        return (size);
    }
}

static void copy_word(const char *str, char *word, int *i)
{
    int j = 0;

    if (check_char(str, *i, '\"')) {
        copy_it(str, word, i, '\"');
        return;
    } else if (check_char(str, *i, '\'')) {
        copy_it(str, word, i, '\'');
        return;
    } else {
        for (; str[*i] && (str[*i] != ' ' && str[*i] != '\t'); ++*i, ++j)
            word[j] = str[*i];
        word[j] = '\0';
        return;
    }
}

char *get_word(const char *str, int *i)
{
    char *word = NULL;
    int size = 0;

    for (; str[*i] && (str[*i] == ' ' || str[*i] == '\t'); ++*i);
    size = get_size_word(str, *i);
    word = malloc(sizeof(char) * (size + 1));
    if (!word)
        return (NULL);
    copy_word(str, word, i);
    return (word);
}