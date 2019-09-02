/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** aux_fct_alias
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include "parsing.h"
#include "execute.h"
#include "mysh.h"
#include "history.h"

int get_arrlen(char **arr)
{
	int i = 0;

	if (arr == NULL)
		return (0);
	for (; arr[i]; i++);
	return (i);
}

static int check_if_new(char *str, l_list_t *list)
{
	if (!str)
		return (1);
	for (; list != NULL; list = list->next) {
		if (strcmp(str, list->new) == 0)
			return (0);
	}
	return (1);
}

void free_alias_stwa(char **arr)
{
	for (int i = 0; arr[i] != NULL; ++i)
		free(arr[i]);
	free(arr);
}

int check_if_remplace_aliases(char *str, l_list_t *list)
{
	char **arr = stwa(str);
	int return_value = 0;

	if (!arr)
		return (1);
	for (int i = 0; arr[i]; i++) {
		if (strcmp(arr[i], "alias") == 0) {
			return_value = check_if_new(arr[i + 1], list);
			free_alias_stwa(arr);
			return (return_value);
		}
	}
	free_alias_stwa(arr);
	return (1);
}
