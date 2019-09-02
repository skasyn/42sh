/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** parsing.h
*/

#ifndef PSU_42SH_2017_PARSING_H
#define PSU_42SH_2017_PARSING_H

#include <stdbool.h>

/*
* ##########################################################
* #                        ENUMS                           #
* ##########################################################
*/

enum SEPARATORS {R_CHEV, L_CHEV, R_D_CHEV, L_D_CHEV, PIPE, S_COL, AND, OR,
    COM};

/*
* ##########################################################
* #                GLOBAL VAR (defined in parsing.c)       #
* ##########################################################
*/

extern const char *separators[];

/*
* ##########################################################
* #                       FUNCTIONS                        #
* ##########################################################
*/

bool is_a_separator(const char *str);
char **concat_com(char **params, int *index);
char **str_to_word_array(const char *str);
char **handle_glob(char **params);
void move_params(char **params);
void clean_n(char *str);
char *handle_spaceless(char *str);
bool check_quotes(char *str);
char **stwa(const char *str);
bool check_char(const char *str, int i, char c);
char *get_word(const char *str, int *i);

#endif //PSU_42SH_2017_PARSING_H
