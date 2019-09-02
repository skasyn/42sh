/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** signal.c
*/

#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

static void my_putstr(const char *str, char add, int fd)
{
    int size = 0;

    for (; str[size] != '\0'; ++size);
    write(fd, str, size);
    if (add != '\0')
        write(fd, &add, 1);
}

void sigint_signal(int signum)
{
    (void)signum;
}

void errno_print(const char *cmd, int signal)
{
    int errnum = errno;

    if (errnum != 0 && errnum != 9 && signal == -1) {
        if (errnum == 2)
            dprintf(2, "%s: Command not found.\n", cmd);
        if (errnum == 13)
            dprintf(2, "%s: Permission denied.\n", cmd);
        if (errnum == ENOEXEC)
            dprintf(2, "%s: Exec format error. Wrong Architecture.\n", cmd);
    }
}

void check_signal(int sig, char *cmd, int signal)
{
    int res = 0;

    errno_print(cmd, signal);
    if (!WIFSIGNALED(sig))
        return;
    res = WTERMSIG(sig);
    if (res == 11)
        my_putstr("Segmentation fault", '\0', 2);
    else if (res == 8)
        my_putstr("Floating exception", '\0', 2);
    else if (res == 6)
        my_putstr("Abort", '\0', 2);
    if (WCOREDUMP(sig))
        my_putstr(" (core dumped)", '\0', 2);
    write(2, "\n", 1);
}