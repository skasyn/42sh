/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** shell
*/

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <netdb.h>
#include "execute.h"
#include "parsing.h"
#include "ll_parser.h"
#include "mysh.h"
#include "history.h"
#include "destroy.h"

int exec_node(shell_t *shell, ll_tree_t *tree)
{
    int status = 0;

    if (tree == NULL || shell->stop_exec)
        return (1);
    if (tree->type >= 0) {
        status = handle_fnct[tree->type](tree, shell);
    } else {
        if (tree->left != NULL)
            status = exec_node(shell, tree->left);
        if (tree->right != NULL)
            status = exec_node(shell, tree->right);
    }
    return (status);
}

char **get_right_params(char *buffer)
{
    char *test = NULL;
    char **glob = NULL;
    char **array = NULL;

    if (buffer == NULL)
        return (NULL);
    test = handle_spaceless(buffer);
    if (!test || check_quotes(test) == false)
        return (NULL);
    array = stwa(test);
    free(test);
    move_params(array);
    glob = handle_glob(array);
    if (glob != NULL) {
        for (int i = 0; array[i]; ++i)
            free(array[i]);
        free(array);
        return (glob);
    }
    return (array);
}

void show_prompt(void)
{
    char hostname[1024] = {0};
    char *path = get_current_dir_name();
    char *dir = NULL;
    struct hostent *h;

    dir = strrchr(path, '/');
    gethostname(hostname, 1023);
    h = gethostbyname(hostname);
    printf("[\e[1m\e[32m%s@%s \e[36m%s\e[0m]$ ",
    getlogin(), h->h_name, dir + 1);
    fflush(stdout);
    free(path);
}

void reset_read(const shell_t *shell, char *buffer)
{
    destroy_string_array(shell->llstruct->array);
    destroy_ll_tree(shell->llstruct->ll_tree);
    shell->llstruct->ll_tree = NULL;
    free(buffer);
    shell->llstruct->array = NULL;
    shell->llstruct->ll_tree = NULL;
}

void remove_last_backslash(char **array)
{
    int pos = 0;

    for (pos = 0; array[pos] != NULL; ++pos);
    pos--;
    if (pos == -1)
        return;
    if (array[pos][strlen(array[pos]) - 1] == '\n')
        array[pos][strlen(array[pos]) - 1] = '\0';
}

void remove_starting_semicolon(char *str)
{
    while (str[0] == ' ' || str[0] == ';') {
        for (int i = 0; str && str[i]; ++i)
            str[i] = str[i + 1];
    }
    while ((int)strlen(str) - 2 >= 0 &&
        (str[strlen(str) - 2] == ' ' || str[strlen(str) - 2] == ';'))
        str[strlen(str) - 2] = '\0';
}

int find_variable_end(const char *str, int *i)
{
    int end;

    (*i)++;
    while ((str[*i] >= 'A' && str[*i] <= 'Z') ||
        (str[*i] >= 'a' && str[*i] <= 'z') ||
        (str[*i] >= '0' && str[*i] <= '9'))
        (*i)++;
    end = (*i) - 1;
    return end;
}

char *get_variable_name(char *str, int *i)
{
    int end = *i;
    int start = *i;
    char *variable = NULL;
    char *env = NULL;
    char *buffer = NULL;

    end = find_variable_end(str, i);
    variable = strndup(str + start + 1, (size_t )end - start);
    if (variable[strlen(variable) - 1] == '\n')
        variable[strlen(variable) - 1] = '\0';
    env = getenv(variable);
    if (env == NULL) {
        dprintf(2, "%s: Undefined variable.\n", variable);
        return (NULL);
    }
    buffer = strdup(str);
    str = realloc(str, strlen(str) - strlen(variable) + strlen(env) + 1);
    strcpy(str + start, env);
    strcpy(str + start + strlen(env), buffer + (*i));
    return (str);
}

char *find_path_variables(char *str)
{
    int single_quotes = 0;

    for (int i = 0; str && str[i] != '\0'; ++i) {
        if (str[i] == '\'')
            single_quotes++;
        if (str[i] == '$' && single_quotes % 2 == 0)
            str = get_variable_name(str, &i);
        if (str == NULL)
            return (NULL);
    }
    return (str);
}

void transform_intro_tree(shell_t *shell, hist_key_t *st)
{
    if (shell->llstruct->array != NULL) {
            //remove_last_backslash(shell->llstruct->array);
            shell->llstruct->array = history_flag(shell->llstruct->array, st);
            write_in_history(st, shell->llstruct->array);
            shell->llstruct->i = 0;
            shell->llstruct->ll_tree = ll_exp(shell->llstruct);
            shell->stop_exec = 0;
            exec_node(shell, shell->llstruct->ll_tree);
        }
}

void read_loop(shell_t *shell)
{
    char *buffer = NULL;
    size_t n = 0;
    int bytes = 0;
    hist_key_t st;

    fill_struc(&st);
    while (!shell->end) {
        show_prompt();
        if (isatty(0)) {
            buffer = read_line(&st);
            bytes = strlen(buffer);
        } else
            bytes = getline(&buffer, &n, stdin);
        if (bytes == 0 || bytes == -1 || buffer[0] == '\0') {
            printf("exit\n");
            free(buffer);
            break;
        }
        remove_starting_semicolon(buffer);
    	buffer = put_aliases(buffer, shell->aliases);
    	buffer = find_path_variables(buffer);
        shell->llstruct->array = get_right_params(buffer);
        transform_intro_tree(shell, &st);
        reset_read(shell, buffer);
        buffer = NULL;
    }
    free(st.path);
}
