NAME = pipex

SRC_DIR = src
BONUS_DIR = srcb
OBJ_DIR = obj

SRC = ${SRC_DIR}/main.c  ${SRC_DIR}/pipex_utils.c \
	${SRC_DIR}/pipex_list_funcs.c ${SRC_DIR}/parse_cmds.c \
	${SRC_DIR}/get_next_line.c ${SRC_DIR}/get_next_line_utils.c \
	${SRC_DIR}/pipex_free.c ${SRC_DIR}/here_doc.c ${SRC_DIR}/pipex_error.c

BONUS = ${BONUS_DIR}/main_bonus.c  ${BONUS_DIR}/pipex_utils_bonus.c \
	${BONUS_DIR}/pipex_list_funcs_bonus.c ${BONUS_DIR}/parse_cmds_bonus.c \
	${BONUS_DIR}/get_next_line_bonus.c ${BONUS_DIR}/get_next_line_utils_bonus.c \
	${BONUS_DIR}/pipex_free_bonus.c ${BONUS_DIR}/here_doc_bonus.c ${BONUS_DIR}/pipex_error_bonus.c

OBJS = ${SRC:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}

BONUS_OBJS = ${BONUS:${BONUS_DIR}/%.c=${OBJ_DIR}/%.o}

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

LIBFT = libft/libft.a

${NAME}: ${OBJS} ${LIBFT}
	${CC} ${OBJS} -o $@ -I. ${LIBFT}

${OBJ_DIR}/%.o:${SRC_DIR}/%.c
	mkdir -p obj
	${CC} ${CFLAGS} -c $< -o $@

${OBJ_DIR}/%.o:${BONUS_DIR}/%.c
	mkdir -p obj
	${CC} ${CFLAGS} -c $< -o $@

${LIBFT}:
	@echo "compiling libft"
	make bonus -C libft/

all: ${NAME}

bonus: ${BONUS_OBJS} ${LIBFT}
	${CC} ${BONUS_OBJS} -o ${NAME} -I. libft/libft.a

clean:
	rm -f ${OBJS} ${BONUS_OBJS}
	make clean -C libft/

fclean: clean
	rm -f ${NAME} 
	rm -f libft/libft.a

re: fclean all

.PHONY: all clean fclean re