# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/21 16:52:30 by isahmed           #+#    #+#              #
#    Updated: 2025/05/16 17:05:45 by isahmed          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Iinc -ILibft/ -Wall -Wextra -Werror -g
CC = gcc
ODIR = objs
SDIR = srcs
LIBFT = Libft/libft.a
BINARY = minishell 
CFILES = minishell.c signals.c  \
	parsing/ast.c parsing/ast_cmd.c parsing/ast_redir.c parsing/ast_utils.c \
	parsing/clean_args.c parsing/heredoc.c \
	parsing/linked_list.c parsing/tokens.c parsing/tokens_utils.c parsing/check_tokens.c \
	execute/env_delete.c execute/cmd_path.c execute/env_create.c execute/env_utils.c\
	execute/exec.c execute/exec_pipe.c execute/exec_redir.c execute/remove_quotes.c execute/param_sub.c execute/wildcards.c\
	execute/exec_cmd.c  execute/wildcard_helpers.c \
	execute/bi_cd.c execute/bi_echo.c execute/bi_export.c execute/bi_the_rest.c \
	utils/ft_strndup.c utils/ft_split2.c utils/utils.c utils/prompt.c utils/debug.c

VPATH = $(SDIR)
OBJECTS = $(CFILES:$(SDIR)/%.c=$(ODIR)/%.o)

all: $(BINARY) 

v valgrind: $(BINARY)
	valgrind --suppressions=debugging/rl.supp --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell

DIRS = $(ODIR)

$(DIRS):
	@mkdir -p $@

i init:
	@git submodule update --init --remote --recursive

$(LIBFT): $(SUBMODULE)
	@make --no-print-directory -C Libft

$(BINARY): $(OBJECTS) 
	$(CC) $(CFLAGS) $^ -o $@  -lreadline

$(ODIR)/%.o: %.c | $(DIRS)
	$(CC) $(CFLAGS) -c $< -o $@ 

bonus: all

clean:
	@make --no-print-directory -C Libft clean
	rm -rf $(ODIR)

$(BINARY): $(OBJECTS) $(LIBFT)

fclean: clean
	@make --no-print-directory -C Libft fclean 
	rm -rf $(BINARY)
	rm -rf $(ODIR)

re: fclean all

.PHONY: all clean fclean re bonus

