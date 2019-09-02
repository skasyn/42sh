/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** autocomplete.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "line_formatting.h"
#include "mysh.h"

void find_path(autocomplete_t *autostruct, char *line)
{
    char *last_slash = strrchr(line, '/');
    char *last_space = strrchr(line, ' ');

    if (last_slash == NULL) {
        if (last_space == NULL)
            autostruct->end = strdup(line);
        else
            autostruct->end = strdup(last_space + 1);
        autostruct->path = strdup("./");
    } else {
        if (last_space == NULL || last_space > last_slash) {
            autostruct->path = strndup(line, last_slash - line + 1);
            autostruct->end = strdup(last_slash + 1);
        } else {
            autostruct->path = strndup(last_space + 1, last_slash - last_space);
            autostruct->end = strdup(last_slash + 1);
        }
    }
}

void autocomplete_one_writing(char *line, int *line_length,
int *cursor, autocomplete_t *autostruct)
{
    if (strncmp(autostruct->end, autostruct->namelist[autostruct->pos]->d_name,
        strlen(autostruct->namelist[autostruct->pos]->d_name)) != 0) {
        for (int i = 0; i < (int)strlen(autostruct->end); ++i)
            backspace(line, line_length, cursor);
        while (*cursor != *line_length) {
            write(1, &line[*line_length], 1);
            (*cursor)++;
        }
        for (int i = 0; i < (int)
            strlen(autostruct->namelist[autostruct->pos]->d_name); ++i)
            letters(line, autostruct->namelist[autostruct->pos]->d_name[i],
                line_length, cursor);
    }
}

void autocomplete_one(char *line, int *line_length, int *cursor,
    autocomplete_t *autostruct)
{
    DIR *fd = NULL;
    char *last_space = NULL;

    for (int i = (*cursor); i < *line_length; ++i)
        write(1, &line[i], 1);
    *cursor = *line_length;
    autocomplete_one_writing(line, line_length, cursor, autostruct);
    last_space = strrchr(line, ' ');
    if (last_space == NULL)
        fd = opendir(line);
    else
        fd = opendir(last_space + 1);
    if (fd != NULL)
        letters(line, '/', line_length, cursor);
    closedir(fd);
}

autocomplete_t *create_autocomplete_struct(char *line)
{
    autocomplete_t *autostruct = malloc(sizeof(autocomplete_t));

    autostruct->end = NULL;
    autostruct->path = NULL;
    autostruct->namelist = NULL;
    autostruct->nb = 0;
    autostruct->number_occurences = 0;
    autostruct->pos = 0;
    find_path(autostruct, line);
    autostruct->nb = scandir(autostruct->path, &autostruct->namelist,
        NULL, alphasort);
    for (int i = 0; i < autostruct->nb; ++i) {
        if (strncmp(autostruct->namelist[i]->d_name, autostruct->end,
            strlen(autostruct->end)) == 0) {
            autostruct->number_occurences++;
            autostruct->pos = i;
        }
    }
    return (autostruct);
}

void autocomplete_other(char *line, int *line_length, int *cursor,
    autocomplete_t *autostruct)
{
    for (int i = (*cursor); i < *line_length; ++i)
        write(1, &line[i], 1);
    *cursor = *line_length;
    write(1, "\n", 1);
    for (int pos = 0; pos < autostruct->nb; ++pos) {
        if (strncmp(autostruct->namelist[pos]->d_name, autostruct->end,
            strlen(autostruct->end)) == 0) {
            write(1, autostruct->namelist[pos]->d_name,
                strlen(autostruct->namelist[pos]->d_name));
            write(1, " ", 1);
        }
    }
    write(1, "\n", 1);
    show_prompt();
    write(1, line, strlen(line));
}

void autostruct_destroy(autocomplete_t *autostruct)
{
    free(autostruct->end);
    free(autostruct->path);
    for (int i = 0; i < autostruct->nb; ++i)
        free(autostruct->namelist[i]);
    free(autostruct->namelist);
    free(autostruct);
}

int autocomplete(char *line, int *line_length, int *cursor)
{
    autocomplete_t *autostruct = create_autocomplete_struct(line);

    if (autostruct->number_occurences == 0) {
        autostruct_destroy(autostruct);
        return (0);
    }
    if (autostruct->number_occurences == 1) {
        autocomplete_one(line, line_length, cursor, autostruct);
        autostruct_destroy(autostruct);
        return (0);
    }
    autocomplete_other(line, line_length, cursor, autostruct);
    autostruct_destroy(autostruct);
    return (0);
}