# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcharpen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 13:52:52 by tcharpen          #+#    #+#              #
#    Updated: 2022/05/09 13:52:56 by tcharpen         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HDR = srcs/minishell.h

SRCS = builtins/cd.c builtins/cd2.c builtins/echo.c builtins/env.c \
builtins/export.c builtins/print_export.c builtins/pwd.c builtins/unset.c \
builtins/exit.c \
execution/builtins.c execution/fork.c execution/execution.c execution/path.c \
execution/pipe.c execution/file.c \
init/init_builtins.c init/init_env.c init/init_path.c init/init.c \
parsing/command.c parsing/free_parsing.c parsing/init_command.c \
parsing/parse.c parsing/pipe.c parsing/quote.c parsing/readline.c \
parsing/redirect_check.c parsing/redirect_limit.c parsing/redirect_open.c \
parsing/redirect_path.c parsing/redirect.c parsing/utils.c \
parsing/variable_malloc.c parsing/variable.c \
utils/env.c utils/ft_same_str.c utils/ft_strcmp.c utils/ft_strjoin_free_s1.c \
utils/ft_stronlyspace.c utils/ft_strpostchr.c utils/ft_strprechr.c \
utils/size_word.c utils/utils.c utils/ft_add_str_in_chain.c utils/ft_itoa.c\
error.c free.c main.c signal.c

OBJS = ${addprefix srcs/,${SRCS:.c=.o}}

LIBFT_AR = libft/libft.a 

INCLUDE_HOME = -I libft
INCLUDE_42 = -I libft -I /Users/tcharpen/.brew/opt/readline/include
LIB_HOME = -Llibft -lft -lreadline
LIB_42 = -Llibft -lft -L/Users/tcharpen/.brew/opt/readline/lib -lreadline

CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

%.o: %.c ${HDR} ${LIBFT_AR} Makefile
	${CC} ${CFLAGS} -c $< -o $@ ${INCLUDE_42}

all: libft ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIB_42}

libft:
	make -C libft

clean:
	rm -f ${OBJS}
	make clean -C libft

fclean: clean
	rm -f ${NAME}
	make fclean -C libft

re: fclean all

.PHONY: all libft clean fclean re
