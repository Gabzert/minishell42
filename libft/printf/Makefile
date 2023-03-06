# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfantech <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 11:21:35 by gfantech          #+#    #+#              #
#    Updated: 2022/11/18 10:50:00 by gfantech         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRCS    =  ft_printf.c ft_printhex.c ft_printchr.c ft_printmem.c ft_printnum.c ft_printun.c \
	   ft_printstr.c ft_format_utils.c ft_formatter.c ft_printer.c
NAME		= libftprintf.a
LIBFT		= srcs
LIBFT_LIB	= srcs.a
OBJS		= $(SRCS:.c=.o)
RM			= rm -f
LIBC		= ar -rcs
FLAGS		= -Wall -Wextra -Werror
INCS		= .
COMPILER	= gcc

.c.o:
	${COMPILER} ${FLAGS} -c $< -o ${<:.c=.o} -I${INCS}

$(NAME): ${OBJS}
	make all -C ../$(LIBFT)/
	cp ../$(LIBFT)/$(LIBFT_LIB) $(NAME)
	${LIBC} $(NAME) $(OBJS)

all: $(NAME)
    
fclean: clean
	$(RM) $(NAME) $(bonus)
	make fclean -C ../$(LIBFT)
    
clean:
	$(RM) -f $(OBJS) $(OBJS_B)
	make clean -C ../$(LIBFT)
    
re: fclean all

bonus: all
              
