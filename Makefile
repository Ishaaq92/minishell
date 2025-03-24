# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/21 16:52:30 by isahmed           #+#    #+#              #
#    Updated: 2025/03/24 11:07:44 by isahmed          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Iinc
CC = gcc
ODIR = objs
SDIR = srcs

VPATH = $(SDIR)

BINARY = minishell 
CFILES = minishell.c
OBJECTS = $(CFILES:$(SDIR)/%.c=$(ODIR)/%.o)
all: $(BINARY)

v valgrind: $(BINARY)
	valgrind --suppressions=debugging/rl.supp --leak-check=full --show-leak-kinds=all --log-file=debugging/valgrind.txt ./minishell
DIRS = $(ODIR)

$(DIRS):
	@mkdir -p $@

$(BINARY): $(OBJECTS) 
	$(CC) $(CFLAGS) $^ -o $@  -lreadline

$(ODIR)/%.o: %.c | $(DIRS)
	$(CC) $(CFLAGS) -c $< -o $@ 

bonus: all

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(BINARY)
	rm -rf $(ODIR)

re: fclean all

.PHONY: all clean fclean re bonus

