# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfantech <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 10:51:21 by gfantech          #+#    #+#              #
#    Updated: 2022/11/30 10:48:41 by gfantech         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJS    = ${SRCS:.c=.o}
INCS    = includes
NAME    = libft.a
LIBC    = ar rc
LIBR    = ranlib
CC      = gcc
RM      = rm -f
CFLAGS  = -Wall -Wextra -Werror

DEF_COLOR = \033[0;39m
GREEN = \033[0;32m
RED = \033[0;91m
CIANO = \033[0;36m

.SILENT:
.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INCS}

${NAME}: ${OBJS}
	make all -C srcs/
	make all -C printf/
	cp srcs/srcs.a ${NAME}
	cp printf/libftprintf.a ${NAME}
	${LIBC} ${NAME} ${OBJS}
	# echo "${GREEN}OK"

all: ${NAME}

clean: 
	${RM} -f ${OBJS}
	make clean -C srcs
	make clean -C printf
	#echo "${CIANO}Pulito"

fclean: clean
	${RM} -f ${NAME}
	make fclean -C srcs
	make fclean -C printf
	#echo "${CIANO}Pulito Tutto"

re: fclean all

