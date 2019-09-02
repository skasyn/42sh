/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** execute.c
*/

#include "execute.h"

int (*handle_fnct[]) (ll_tree_t *, shell_t *) = {
    handle_com,
    handle_and,
    handle_or,
    handle_pipe,
    handle_left,
    handle_d_left,
    handle_right,
    handle_d_right,
    handle_semi,
    handle_file
};