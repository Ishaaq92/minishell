# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/21 16:52:30 by isahmed           #+#    #+#              #
#    Updated: 2025/03/24 14:19:07 by isahmed          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Iinc -ILibft/
CC = gcc
ODIR = objs
SDIR = srcs
LIBFT = Libft/libft.a
BINARY = minishell 
CFILES = minishell.c

VPATH = $(SDIR)
OBJECTS = $(CFILES:$(SDIR)/%.c=$(ODIR)/%.o)

all: $(BINARY)

v valgrind: $(BINARY)
	valgrind --suppressions=debugging/rl.supp --leak-check=full --show-leak-kinds=all --log-file=debugging/valgrind.txt ./minishell

DIRS = $(ODIR)

$(DIRS):
	@mkdir -p $@

$(LIBFT):
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

