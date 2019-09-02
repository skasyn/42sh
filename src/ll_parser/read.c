/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** read.c
*/

#include <string.h>
#include <stdlib.h>
#include "ll_parser.h"

bool ll_read_token(ll_struct_t *llstruct, char *str)
{
    if (llstruct->array[llstruct->i] == NULL)
        return (false);
    if (strcmp(llstruct->array[llstruct->i], str) == 0) {
        llstruct->i++;
        return (true);
    }
    return (false);
}

bool ll_read_left(ll_struct_t *llstruct)
{
    if (ll_read_token(llstruct, OPE_S_LEFT)
        || ll_read_token(llstruct, OPE_D_LEFT))
        return (true);
    return (false);
}

bool ll_read_right(ll_struct_t *llstruct)
{
    if (ll_read_token(llstruct, OPE_S_RIGHT)
        || ll_read_token(llstruct, OPE_D_RIGHT))
        return (true);
    return (false);
}

bool ll_word(ll_struct_t *llstruct)
{
    if (llstruct->array[llstruct->i] == NULL)
        return (false);
    if (!(ll_read_token(llstruct, OPE_AND) || ll_read_token(llstruct, OPE_OR)
    || ll_read_token(llstruct, OPE_PIPE) || ll_read_token(llstruct, OPE_SEMI)
    || ll_read_left(llstruct) || ll_read_right(llstruct))) {
        return (true);
    }
    llstruct->i--;
    return (false);
}