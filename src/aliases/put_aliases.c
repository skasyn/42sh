/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** put_aliases
*/

#include "mysh.h"
#include <string.h>
#include <stdlib.h>

int check_if_alias(char *str, char *new, int i)
{
    unsigned int j = 0;

    while (str[i] == new[j] && new[j] && str[i]) {
            i++;
            j++;
    }
    if (j == strlen(new) && (str[i] != 'a' && str[i] != 'l' && str[i] != 'i'
			     && str[i] != 's')) {
	    return (0);
    }
    return (1);
}

char *get_new_str(char *str, char *new, char *old, int get_old)
{
    char *new_str = malloc(sizeof(char) * (strlen(str) + strlen(old) + 1));
    unsigned int j = 0;
    int i = 0;

    if (new_str == NULL)
        exit(84);
    for (; i < get_old && str[j]; i++) {
        new_str[i] = str[j];
        j++;
    }
    for (get_old = 0; old[get_old]; get_old++) {
        new_str[i] = old[get_old];
        i++;
    }
    for (j = j + strlen(new); str[j]; j++) {
        new_str[i] = str[j];
        i++;
    }
    new_str[i] = '\0';
    free(str);
    return (new_str);
}

char *put_aliases(char *str, l_list_t *list)
{
	unsigned int i = 0;
	l_list_t *tmp = list;

	if (check_if_remplace_aliases(str, tmp)  == 0)
		return (str);
	for (; tmp != NULL; tmp = tmp->next) {
		for (i = 0; str[i]
		&& check_if_alias(str, tmp->new, i) == 1; i++);
		if (i < strlen(str) - 1)
			str = get_new_str(str, tmp->new, tmp->old, i);
	}
	return (str);
}
