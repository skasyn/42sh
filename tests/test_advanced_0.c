/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** advanced tests
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

Test(shell, advanced_test, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array =
	get_right_params("cd ; </etc/hosts od -c | grep xx |\
wc >> /tmp/z -l ; cd - && echo OK");
	if (shell->llstruct->array != NULL) {
		shell->llstruct->i = 0;
		shell->llstruct->ll_tree = ll_exp(shell->llstruct);
		exec_node(shell, shell->llstruct->ll_tree);
		destroy_string_array(shell->llstruct->array);
		destroy_ll_tree(shell->llstruct->ll_tree);
	}
	cr_assert_stdout_eq_str("OK\n");
}

Test(shell, advanced_cocktail_test, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array =
	get_right_params("cat tests/test/caca ; cat tests/test/caca && ls Makefile");
	if (shell->llstruct->array != NULL) {
		shell->llstruct->i = 0;
		shell->llstruct->ll_tree = ll_exp(shell->llstruct);
		exec_node(shell, shell->llstruct->ll_tree);
		destroy_string_array(shell->llstruct->array);
		destroy_ll_tree(shell->llstruct->ll_tree);
	}
	cr_assert_stdout_eq_str("aaMakefile\n");
}

Test(shell, advanced_cocktail_redirection, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array =
	get_right_params("echo -n a > tests/test/caca ; echo -n b >> tests/test/caca\
; cat tests/test/caca ; echo -n a > tests/test/caca");
	if (shell->llstruct->array != NULL) {
		shell->llstruct->i = 0;
		shell->llstruct->ll_tree = ll_exp(shell->llstruct);
		exec_node(shell, shell->llstruct->ll_tree);
		destroy_string_array(shell->llstruct->array);
		destroy_ll_tree(shell->llstruct->ll_tree);
	}
	cr_assert_stdout_eq_str("ab");
}

Test(shell, test_echo_inibitor, .init = redirect_all_std)
{
	shell_t *shell = create_shell(environ);

	shell->llstruct->array =
	get_right_params("echo \"\\\" | cat -e");
	if (shell->llstruct->array != NULL) {
		shell->llstruct->i = 0;
		shell->llstruct->ll_tree = ll_exp(shell->llstruct);
		exec_node(shell, shell->llstruct->ll_tree);
		destroy_string_array(shell->llstruct->array);
		destroy_ll_tree(shell->llstruct->ll_tree);
	}
	cr_assert_stdout_eq_str("\\$\n");
}
