/*
** EPITECH PROJECT, 2018
** history flag
** File description:
** history flag
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "history.h"
#include "parsing.h"

int arr_len(char **str)
{
    int i = 0;

    while (str[i] != NULL) {
        i++;
    }
    return (i);
}

char **fill_dest(char **dest, char **arr, char **str)
{
    int i = 0;

    for (int j = 0; arr[j] != NULL; j++) {
        dest[i] = strdup(arr[j]);
        i++;
    }
    for (int j = 1; str[j] != NULL; ++j) {
        dest[i] = strdup(str[j]);
        i++;
    }
    dest[i] = NULL;
    return (dest);
}

char **check_command(history_t *st, char **dest, char **str)
{
    char *line = NULL;
    char **arr = NULL;
    size_t len = 0;

    getline(&line, &len, st->fp);
    if (strncmp(line, st->command, strlen(st->command)) != 0) {
        return (NULL);
    }
    if (line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';
    arr = stwa(line);
    if ((dest = malloc(sizeof(char *) * \
    (arr_len(arr) + arr_len(str)))) == NULL) {
        st->check = 84;
        return (NULL);
    }
    dest = fill_dest(dest, arr, str);
    st->check = 1;
    free_all(arr, str, line);
    return (dest);
}

char **find_command(history_t *st, char **dest, char **str, hist_key_t *key)
{
    int i = -2;
    char c = 'o';

    st->check = 0;
    st->fp = fopen(key->path, "r+");
    fseek(st->fp, -2, SEEK_END);
    while (st->check != 1 && st->check != 84) {
        c = fgetc(st->fp);
        if (c == '\n') {
            fseek(st->fp, i + 1, SEEK_END);
            dest = check_command(st, dest, str);
            fseek(st->fp, i, SEEK_END);
        }
        i = i - 1;
        if (fseek(st->fp, i, SEEK_END) == -1)
            st->check = 84;
    }
    fclose(st->fp);
    return (dest);
}

char **history_flag(char **str, hist_key_t *key)
{
    char **dest = NULL;
    history_t st;

    if (str[0] == NULL || str[0][0] != '!' ||
        str[0][1] == '\0' || str[0][1] == '\n')
        return (str);
    if ((st.command = strdup(str[0] + 1)) == NULL)
        return (str);
    if ((dest = find_command(&st, dest, str, key)) == NULL) {
        free(st.command);
        return (str);
    }
    free(st.command);
    return (dest);
}
