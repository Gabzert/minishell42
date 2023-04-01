#####################
# GENERIC VARIABLES #
#####################

NAME    = minishell
INCS    = includes
CC      = gcc
RM      = rm -f
CFLAGS  = -Wall -Wextra -Werror
OBJDIR  = obj/
SRCDIR  =
B_DIR	=

#########
# FILES #
#########

SRCS    = $(wildcard *.c)

OBJS    = $(addprefix $(OBJDIR),$(SRCS:.c=.o))

B_SRCS  = main.c utils.c pipes.c

B_FILES = 

B_OBJS  = $(addprefix $(OBJDIR),$(B_SRCS:.c=.o))

##########
# COLORS #
##########

DEF_COLOR = \033[0;33m
GREEN = \033[0;32m
RED = \033[0;91m
CIANO = \033[0;36m

.SILENT:

all: ${NAME}

${OBJDIR}%.o: ${SRCDIR}%.c
	@mkdir -p obj
	$(CC) -g $(CFLAGS) -c $< -o $@ -I${INCS}

${OBJDIR}%.o: ${B_DIR}%.c
	@mkdir -p obj
	$(CC) -g $(CFLAGS) -c $< -o $@ -I${INCS}

${NAME}: ${OBJS}
	make all -C libft
	cp libft/libft.a ${CURDIR}
	${CC} -g ${OBJS} ${CFLAGS} -lreadline -o ${NAME}  libft.a
	${RM} -f libft.a
	echo "${GREEN}OK"

debug: ${OBJS}
	${CC} ${CFLAGS} -g -o ${NAME} ${OBJS}
	echo "${DEF_COLOR}DEBUG READY"

bonus: ${B_OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${B_OBJS}

clean:
	${RM} -rf ${OBJDIR}
	make clean -C libft
	echo "${CIANO}Pulito"

fclean: clean
	${RM} -f ${NAME}
	make fclean -C libft
	echo "${CIANO}Tutto"

re: fclean all
