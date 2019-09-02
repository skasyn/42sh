/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** line_formatting.h
*/

#ifndef PSU_42SH_2017_LINE_FORMATTING_H
#define PSU_42SH_2017_LINE_FORMATTING_H

typedef struct autocomplete_s {
    char *end;
    char *path;
    struct dirent **namelist;
    int nb;
    int number_occurences;
    int pos;
} autocomplete_t;

void backspace(char *line, int *line_length, int *cursor);
int letters(char *line, char ch, int *line_length, int *cursor);
int autocomplete(char *line, int *line_length, int *cursor);

#endif //PSU_42SH_2017_LINE_FORMATTING_H
