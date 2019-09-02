/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** basic tests
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

Test(shell, basic_inhibitor, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array = get_right_params("&&");
	if (shell->llstruct->array != NULL) {
		shell->llstruct->i = 0;
		shell->llstruct->ll_tree = ll_exp(shell->llstruct);
		exec_node(shell, shell->llstruct->ll_tree);
		destroy_string_array(shell->llstruct->array);
		destroy_ll_tree(shell->llstruct->ll_tree);
	}
	cr_assert_stdout_eq_str("\n");
}

Test(shell, basic_env, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array = get_right_params("unsetenv * ; setenv Pas Tek ; env");
	if (shell->llstruct->array != NULL) {
		shell->llstruct->i = 0;
		shell->llstruct->ll_tree = ll_exp(shell->llstruct);
		exec_node(shell, shell->llstruct->ll_tree);
		destroy_string_array(shell->llstruct->array);
		destroy_ll_tree(shell->llstruct->ll_tree);
	}
	cr_assert_stdout_eq_str("Pas=Tek\n");
}

Test(shell, basic_cd, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array = get_right_params("cd tests/test && cd . ; cd .. ||\
cd - && cd - ; cd . ; cd test && ls");
	if (shell->llstruct->array != NULL) {
		shell->llstruct->i = 0;
		shell->llstruct->ll_tree = ll_exp(shell->llstruct);
		exec_node(shell, shell->llstruct->ll_tree);
		destroy_string_array(shell->llstruct->array);
		destroy_ll_tree(shell->llstruct->ll_tree);
	}
	cr_assert_stdout_eq_str("allah\ncaca\ncrash\nhaha\n");
}

Test(shell, basic_unsetenv, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array = get_right_params("unsetenv");
	if (shell->llstruct->array != NULL) {
		shell->llstruct->i = 0;
		shell->llstruct->ll_tree = ll_exp(shell->llstruct);
		exec_node(shell, shell->llstruct->ll_tree);
		destroy_string_array(shell->llstruct->array);
		destroy_ll_tree(shell->llstruct->ll_tree);
	}
	cr_assert_stderr_eq_str("unsetenv: Too few arguments.\n");
}
