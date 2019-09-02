/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** test_2
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

Test(shell, basic_separator, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array =
	get_right_params("setenv yo oy ; cd tests/test ; cat caca");
	if (shell->llstruct->array != NULL) {
		shell->llstruct->i = 0;
		shell->llstruct->ll_tree = ll_exp(shell->llstruct);
		exec_node(shell, shell->llstruct->ll_tree);
		destroy_string_array(shell->llstruct->array);
		destroy_ll_tree(shell->llstruct->ll_tree);
	}
	cr_assert_stdout_eq_str("a");
}

Test(shell, basic_backtick, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array =
	get_right_params("echo quoi`echo feur`");
	if (shell->llstruct->array != NULL) {
		shell->llstruct->i = 0;
		shell->llstruct->ll_tree = ll_exp(shell->llstruct);
		exec_node(shell, shell->llstruct->ll_tree);
		destroy_string_array(shell->llstruct->array);
		destroy_ll_tree(shell->llstruct->ll_tree);
	}
	cr_assert_stdout_eq_str("quoifeur\n");
}

Test(shell, evil_test_0, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array =
	get_right_params("; ls Makefile");
	if (shell->llstruct->array != NULL) {
		shell->llstruct->i = 0;
		shell->llstruct->ll_tree = ll_exp(shell->llstruct);
		exec_node(shell, shell->llstruct->ll_tree);
		destroy_string_array(shell->llstruct->array);
		destroy_ll_tree(shell->llstruct->ll_tree);
	}
	cr_assert_stdout_eq_str("Makefile\n");
}

Test(shell, evil_test_1, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array =
	get_right_params("ls Makefile ;");
	if (shell->llstruct->array != NULL) {
		shell->llstruct->i = 0;
		shell->llstruct->ll_tree = ll_exp(shell->llstruct);
		exec_node(shell, shell->llstruct->ll_tree);
		destroy_string_array(shell->llstruct->array);
		destroy_ll_tree(shell->llstruct->ll_tree);
	}
	cr_assert_stdout_eq_str("Makefile\n");
}

Test(shell, basic_redirection, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array =
	get_right_params("cat < tests/test/caca");
	if (shell->llstruct->array != NULL) {
		shell->llstruct->i = 0;
		shell->llstruct->ll_tree = ll_exp(shell->llstruct);
		exec_node(shell, shell->llstruct->ll_tree);
		destroy_string_array(shell->llstruct->array);
		destroy_ll_tree(shell->llstruct->ll_tree);
	}
	cr_assert_stdout_eq_str("a");
}
