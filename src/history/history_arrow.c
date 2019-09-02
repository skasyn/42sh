/*
** EPITECH PROJECT, 2018
** test
** File description:
** test
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mysh.h"
#include "history.h"

void free_arr(char **str)
{
    int i = 0;

    while (str[i] != NULL) {
        free(str[i]);
        i++;
    }
    free(str);
}

int one_by_one(char *line, char ch, int *line_length, int *cursor)
{
    write(1, &ch, 1);
    if ((*line_length) == MAX_READ_LINE - 2)
        return (1);
    if ((*cursor) == (*line_length)) {
        line[(*line_length)++] = ch;
    } else {
        (*line_length)++;
        for (int i = (*line_length); i > (*cursor); --i)
            line[i] = line[i - 1];
        line[(*cursor)] = ch;
        for (int i = (*cursor) + 1; i < (*line_length); ++i)
            write(1, &line[i], 1);
        ch = 8;
        for (int i = (*cursor) + 1; i < (*line_length); ++i)
            write(1, &ch, 1);
    }
    (*cursor)++;
    return (0);
}

int print_in_input(char *command, char *line, int *line_length, int *cursor)
{
    int i = 0;

    for (int u = *cursor; u < *line_length; ++u)
        write(1, &line[u], 1);
    *cursor = *line_length;
    while (*line_length != 0)
        backspace(line, line_length, cursor);
    if (command == NULL)
        return (0);
    while (command[i] != '\n' && command[i] != '\0') {
        if (one_by_one(line, command[i], line_length, cursor) == 1)
            return (0);
        i++;
    }
    free(command);
    return (0);
}

int arrow_down(hist_key_t *st, char *line, int *line_length, int *cursor)
{
    FILE *fp = fopen(st->path, "r+");
    char *command = NULL;
    size_t len = 0;
    char c = 'o';

    if (st->x >= -3)
        return (0);
    st->x = st->x + 2;
    fseek(fp, (st->x), SEEK_END);
    while (c != '\n') {
        c = fgetc(fp);
        st->x = st->x + 1;
        fseek(fp, st->x, SEEK_END);
    }
    fseek(fp, st->x, SEEK_END);
    command = get_command(command, len, fp, st);
    print_in_input(command, line, line_length, cursor);
    return (0);
}

int arrow_up(hist_key_t *st, char *line, int *line_length, int *cursor)
{
    FILE *fp = fopen(st->path, "r+");
    char *command = NULL;
    size_t len = 0;

    if (fseek(fp, st->x, SEEK_END) == -1)
        return (0);
    move_in_file(fp, st);
    st->x = st->x + 1;
    if (st->x == -1)
        return (0);
    fseek(fp, st->x + 1, SEEK_END);
    command = get_command(command, len, fp, st);
    print_in_input(command, line, line_length, cursor);
    return (0);
}
