/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** test_1.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include "execute.h"
#include "parsing.h"
#include "ll_parser.h"
#include "mysh.h"
#include "destroy.h"

extern char **environ;

void redirect_all_std(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

Test(shell, basic_ls, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array = get_right_params("ls Makefile");
    if (shell->llstruct->array != NULL) {
        shell->llstruct->i = 0;
        shell->llstruct->ll_tree = ll_exp(shell->llstruct);
        exec_node(shell, shell->llstruct->ll_tree);
        destroy_string_array(shell->llstruct->array);
        destroy_ll_tree(shell->llstruct->ll_tree);
    }
	cr_assert_stdout_eq_str("Makefile\n");
}

Test(shell, basic_pipe, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array =
	get_right_params("echo \"Hello!\" | tr \"[:lower:]\" \"[:upper:]\"");
    if (shell->llstruct->array != NULL) {
        shell->llstruct->i = 0;
        shell->llstruct->ll_tree = ll_exp(shell->llstruct);
        exec_node(shell, shell->llstruct->ll_tree);
    }
	cr_assert_stdout_eq_str("HELLO!\n");
}

Test(shell, basic_variables, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array = get_right_params("echo $TERM\n");
	if (shell->llstruct->array != NULL) {
        shell->llstruct->i = 0;
        shell->llstruct->ll_tree = ll_exp(shell->llstruct);
        exec_node(shell, shell->llstruct->ll_tree);
    }
	cr_assert_stdout_eq_str("xterm-256color");
}

Test(shell, basic_quote, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array = get_right_params("echo salut\"");
	if (shell->llstruct->array != NULL) {
        shell->llstruct->i = 0;
        shell->llstruct->ll_tree = ll_exp(shell->llstruct);
        exec_node(shell, shell->llstruct->ll_tree);
    }
	cr_assert_stderr_eq_str("Unmatched '\"'.\n");
}
