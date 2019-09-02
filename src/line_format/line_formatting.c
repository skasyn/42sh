/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** line_formatting.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <termcap.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include "mysh.h"
#include "history.h"
#include "line_formatting.h"

/*
* ##############################################################
* #                LINE FORMATTING                             #
* ##############################################################
*
* Character values :
* 10 = Enter
* 4 || 0 = Ctrl + D
* 32 <-> 126 = Letters
* 8 || 127 = Backspace
* 12 = CTRL+L
* 27 = Escape sequences (Special values)
* 27 91 65 = Up Arrow
* 27 91 66 = Down Arrow
* 27 91 67 = Right arrow
* 27 91 68 = Left arrow
* 27 91 49 59 53 67 = CTRL + Right arrow
* 27 91 49 59 53 68 = CTRL + Left arrow
*/
void move_cursor(const char *line, int line_length, int *cursor, int way)
{
    char ch = 0;

    if (way == 1) {
        if ((*cursor) < line_length) {
            ch = line[(*cursor)];
            write(1, &ch, 1);
            (*cursor)++;
        }
    }
    if (way == -1) {
        if ((*cursor) > 0) {
            ch = 8;
            write(1, &ch, 1);
            (*cursor)--;
        }
    }
}

void ctrl_arrows(const char *line, int line_length, int *cursor)
{
    char additional[3] = {0, 0, 0};

    read(0, &additional[0], 1);
    read(0, &additional[1], 1);
    read(0, &additional[2], 1);
    if (additional[0] == 59 && additional[1] == 53 && additional[2] == 67) {
        move_cursor(line, line_length, cursor, 1);
        while ((*cursor) < line_length && line[*cursor] != ' ')
            move_cursor(line, line_length, cursor, 1);
    }
    if (additional[0] == 59 && additional[1] == 53 && additional[2] == 68) {
        move_cursor(line, line_length, cursor, -1);
        while ((*cursor) > 0 && line[*cursor] != ' ')
            move_cursor(line, line_length, cursor, -1);
    }
}

void suppr_readline(char *line, int *line_length, int *cursor,
char *escape_sequence)
{
    read(0, &escape_sequence[0], 1);
    if (*cursor != *line_length) {
            write(1, " ", 1);
            (*cursor)++;
            backspace(line, line_length, cursor);
    }
}

void special_values(char *line, int *line_length, int *cursor, hist_key_t *st)
{
    char escape_sequence[2] = {0, 0};

    read(0, &escape_sequence[0], 1);
    read(0, &escape_sequence[1], 1);
    if (escape_sequence[0] == 91 && escape_sequence[1] == 51)
        suppr_readline(line, line_length, cursor, escape_sequence);
    if (escape_sequence[0] == 91 && escape_sequence[1] == 68)
        move_cursor(line, *line_length, cursor, -1);
    if (escape_sequence[0] == 91 && escape_sequence[1] == 67)
        move_cursor(line, *line_length, cursor, 1);
    if (escape_sequence[0] == 91 && escape_sequence[1] == 66)
        arrow_down(st, line, line_length, cursor);
    if (escape_sequence[0] == 91 && escape_sequence[1] == 65)
        arrow_up(st, line, line_length, cursor);
    if (escape_sequence[0] == 91 && escape_sequence[1] == 49)
        ctrl_arrows(line, *line_length, cursor);
}

int letters(char *line, char ch, int *line_length, int *cursor)
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

void backspace(char *line, int *line_length, int *cursor)
{
    char backspace = 8;
    char space = ' ';

    if ((*cursor) == (*line_length)) {
        line[(*cursor)] = '\0';
        write(1, "\b \b", 3);
    } else {
        write(1, &backspace, 1);
        for (int i = (*cursor); i <= (*line_length); ++i)
            write(1, &space, 1);
        for (int i = (*cursor); i <= (*line_length); ++i)
            write(1, &backspace, 1);
        for (int i = (*cursor); i < (*line_length); ++i)
            write(1, &line[i], 1);
        for (int i = (*cursor); i < (*line_length); ++i)
            write(1, &backspace, 1);
        for (int i = (*cursor) - 1; i <= (*line_length); ++i)
            line[i] = line[i + 1];
    }
    (*line_length)--;
    (*cursor)--;
}

char check_ch_returning(char *line, int *line_length,
int *cursor, char ch)
{
    if (ch == 10) {
        line[*line_length] = '\n';
        write(1, &ch, 1);
        return (1);
    }
    if (ch == 4 || ch == '\0') {
        line[*line_length] = '\0';
        return (1);
    }
    if (ch >= 32 && ch <= 126) {
        if (letters(line, ch, line_length, cursor))
            return (1);
    }
    if (ch == '\t')
        autocomplete(line, line_length, cursor);
    return (0);
}

int loop_read_line(char *line, int *line_length, int *cursor, hist_key_t *st)
{
    char ch = 0;

    read(0, &ch, 1);
    if (check_ch_returning(line, line_length, cursor, ch))
        return (1);
    if ((ch == 8 || ch == 127) && *line_length != 0 && *cursor != 0)
        backspace(line, line_length, cursor);
    if (ch == 27)
        special_values(line, line_length, cursor, st);
    if (ch == 12) {
        write(1, "\e[1;1H\e[2J", 11);
        show_prompt();
        write(1, line, strlen(line));
    }
    return (0);
}

char *read_line(hist_key_t *st)
{
    char *line = malloc(sizeof(char) * MAX_READ_LINE);
    struct termios orig_attr;
    int line_length = 0;
    int cursor = 0;
    int end = 0;

    st->x = 0;
    create_bash_history(st);
    tcgetattr(0, &orig_attr);
    set_tty_non_canon();
    for (int i = 0; i < MAX_READ_LINE; ++i)
        line[i] = '\0';
    while (!end) {
        if (loop_read_line(line, &line_length, &cursor, st))
            break;
    }
    tcsetattr(0, TCSANOW, &orig_attr);
    return (line);
}
