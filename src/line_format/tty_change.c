/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** tty_change.c
*/

#include <termcap.h>
#include <termios.h>

void set_tty_non_canon(void)
{
    struct termios tty_attr;

    tcgetattr(0, &tty_attr);
    tty_attr.c_lflag &= (~(ICANON | ECHO));
    tty_attr.c_cc[VTIME] = 0;
    tty_attr.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &tty_attr);
}
