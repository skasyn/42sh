##
## EPITECH PROJECT, 2019
## PROJECT NAME
## File description:
## UNBELIEVABLE DESCRIPTION
##

SRC		=	src/shell/shell.c	\
			src/shell/init.c	\
			src/shell/destroy.c	\
			src/parsing_fncts/handle_glob.c	\
			src/parsing_fncts/get_word_swta.c	\
			src/parsing_fncts/new_swta2.c	\
			src/parsing_fncts/handle_spaceless.c	\
			src/parsing_fncts/check_quotes.c	\
			src/parsing_fncts/concat_com.c	\
			src/parsing_fncts/move_params.c	\
			src/parsing_fncts/handle_b_tree.c	\
			src/aliases/linked_list_alias.c	\
			src/aliases/fct_aux_alias.c	\
			src/aliases/put_aliases.c	\
			src/aliases/builtin_alias.c	\
			src/history/history_flag.c	\
			src/history/write_in_history.c	\
			src/history/history_arrow.c	\
			src/history/history_utility.c	\
			src/global_var/parsing.c	\
			src/global_var/execute.c	\
			src/main.c	\
			src/line_format/line_formatting.c	\
			src/line_format/autocomplete.c	\
			src/line_format/tty_change.c	\
			src/ll_parser/get_exp.c	\
			src/ll_parser/parser_utils.c	\
			src/ll_parser/file_command.c	\
			src/ll_parser/read.c	\
			src/ll_parser/big_nodes.c	\
			src/ll_parser/redirections.c	\
			src/execution/handling_redirect.c	\
			src/execution/handling_operators.c	\
			src/execution/signal.c	\
			src/execution/builtins.c	\
			src/execution/handling_double_left.c	\
			src/execution/builtin_cd.c	\
			src/execution/execution_utils.c	\
			src/execution/builtin_env_unsetenv.c	\
			src/execution/builtin_setenv.c	\


SRCS		=	$(SRC)

TSRCS		:=	$(SRC)

TSRCS		+=	tests/test_basic_0.c\
				tests/test_advanced_0.c\
				tests/test_basic_1.c\
				tests/test_basic_2.c\


TNAME		=	test_42.test

OBJ		=	$(addsuffix .o, $(basename $(SRCS)))

NAME		=	42sh

CC		=	gcc

CFLAGS		=	

CPPFLAGS	=	-Wall -Wextra -I./include/

LDFLAGS		=	

LDLIBS		=	

all:	$(NAME)

tests_run:
	@echo -e "[32m\n==== [92mCOMPILING TESTS[32m ====[0m"
	@$(MAKE) -s re
	@$(CC) $(TFLAGS) -o $(TNAME) $(TSRCS) $(LDLIBS) -lcriterion
	@./$(TNAME)

$(NAME):	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ)
	@echo -e "[32m\n==== [92mCOMPLETED[32m ====[0m"

clean:
	@$(RM) $(OBJ)
	@echo -en "[32m[OK][0m"
	@echo -e "[91m [CLEANING][0m"

clean_tobjs:	clean
	@$(RM) $(wildcard *.gcda)
	@$(RM) $(wildcard *.gcno)
	@$(RM) $(wildcard *.c.gcov)
	@echo -en "[32m[OK][0m"
	@echo -e "[91m [CLEANING TESTS][0m"

fclean:	clean clean_tobjs
	@$(RM) $(NAME)
	@$(RM) $(TNAME)
	@echo -en "[32m[OK][0m"
	@echo -e "[91m [FCLEANING][0m"

re:	fclean all

%.o:	%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -c -o $@ $< \
	&& echo -e "[32m[OK]\e[1m[32m" $< "[0m" || echo -e "ERROR" $<

.PHONY: all clean fclean re tests_run clean_tobjs