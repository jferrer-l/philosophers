SRCS = main.c utils/utils1.c utils/utils2.c sanitize_input.c free_funcs.c thread_handler.c

SRCSBONUS = main.c utils/utils1.c utils/utils2.c sanitize_input.c free_funcs.c thread_handler.cc

NAME = philo
NAMEBONUS = philo_bonus
HEADER = includes/philo.h
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -MMD
OBJS = ${SRCS:.c=.o}
OBJSBONUS =	${SRCSBONUS:.c=.o}
DEP = ${SRCS:.c=.d}
#LINKING_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
#COMFILE_FLAGS = -I${HOME}/.brew/opt/readline/include

.c.o:
	${CC} ${CFLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEADER}
			@echo "\033[36m"--Compilando--"\033[0m ";
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}
			@clear

all:		${NAME}

-include		${DEP}

bonus:		${OBJSBONUS} ${HEADER}
			${CC} ${CFLAGS} ${OBJSBONUS} -o ${NAMEBONUS}
			@touch $@

clean: 		
			${RM} ${OBJS} ${OBJSBONUS} ${DEP}
			@clear
			@echo "\033[34m"🗑️\  Todo depurado correctamente  \🗑️"\033[0m"

fclean: 	clean
			${RM} ${NAME} ${NAMEBONUS}
			${RM} bonus
			@clear
			@echo "\033[34m"🗑️\  Todo depurado correctamente  \🗑️"\033[0m"

re:			fclean all

.PHONY: all clean fclean re
