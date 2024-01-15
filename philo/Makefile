################################################################################
#                                     CONFIG                                   #
################################################################################

NAME     := philo
CC       := gcc
FLAGS    := -Wall -Wextra -Werror -Iinclude -fsanitize=thread -g
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=            srcs/philosophers.c \
                          srcs/main/actions.c \
                          srcs/main/parsing.c \
                          srcs/main/philo_does.c \
                          srcs/main/prepare.c \
                          srcs/main/routines.c \
                          srcs/main/safe_data.c \
                          srcs/utils/ft_atoi.c \
                          srcs/utils/ft_atol.c \
                          srcs/utils/ft_error.c \
                          srcs/utils/ft_found.c \
                          srcs/utils/ft_get_time.c \
                          srcs/utils/ft_input_check.c \
                          srcs/utils/ft_safe_mutex.c \
                          srcs/utils/ft_safe_thread.c \
                          srcs/utils/ft_strcmp.c \
                          srcs/utils/ft_usleep.c 
                          
OBJS        := $(SRCS:.c=.o)
DEPS        := $(SRCS:.c=.d)

.c.o:
	${CC} ${FLAGS} -MMD -c $< -o $@

# .c.d:
# 	@${CC} ${FLAGS} -MM $< -MT ${@:.d=.o} > $@

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS} Makefile include/philosophers.h
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS} ${INCLUDES}
			@echo "$(GREEN)$(NAME) created ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ ${RM} *.d */*.d */*/*.d
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)deps ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

-include ${DEPS}

.PHONY:		all clean fclean re


