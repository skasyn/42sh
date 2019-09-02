/*
** EPITECH PROJECT, 2018
** history utility
** File description:
** history utility
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "history.h"

void free_all(char **arr, char **str, char *line)
{
    free_arr(arr);
    free_arr(str);
    free(line);
}

char *get_command(char *command, size_t len, FILE *fp, hist_key_t *st)
{

    if (st->x == 0)
        return (NULL);
    getline(&command, &len, fp);
    fclose(fp);
    return (command);
}

void fill_struc(hist_key_t *st)
{
    char buff[256];

    st->x = 0;
    if ((st->path = strdup(strcat(getcwd(buff, 256), "/.bash_history"))) \
    == NULL)
        exit(84);
}

void create_bash_history(hist_key_t *st)
{
    int fd = 0;

    fd = open(st->path, O_RDWR | O_CREAT, S_IRWXU);
    close(fd);
}

void move_in_file(FILE *fp, hist_key_t *st)
{
    int i = 0;
    char c = 'o';

    while (i < 2) {
        c = fgetc(fp);
        if (c == '\n')
            i++;
        st->x = st->x - 1;
        if (fseek(fp, st->x, SEEK_END) == -1) {
            i = 2;
            st->x = st->x - 1;
        }
    }
}