/*
** EPITECH PROJECT, 2018
** write in history
** File description:
** write in history
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "history.h"

void write_in_history(hist_key_t *st, char **str)
{
    int fd = 0;
    int i = 0;

    fd = open(st->path, O_WRONLY | O_APPEND);
    while (str[i] != NULL) {
        if (i != 0)
            write(fd, " ", 1);
        write(fd, str[i], strlen(str[i]));
        i++;
    }
    write(fd, "\n", 1);
    close(fd);
}