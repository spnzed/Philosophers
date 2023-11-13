################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := philosophers
CC          := gcc
FLAGS       := -Wall -Wextra -Werror 
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      srcs/main/actions.c \
                    srcs/main/init.c \
                    srcs/main/parsing.c \
                    srcs/main/threads.c \
                    srcs/philosophers.c \
                    srcs/utils/ft_atoi.c \
                    srcs/utils/ft_atol.c \
                    srcs/utils/ft_clear_data.c \
                    srcs/utils/ft_error.c \
                    srcs/utils/ft_exit.c \
                    srcs/utils/ft_found.c \
                    srcs/utils/ft_get_time.c \
                    srcs/utils/ft_input_check.c \
                    srcs/utils/ft_safe_malloc.c \
                    srcs/utils/ft_strcmp.c \
                    srcs/utils/ft_usleep.c \
                          
OBJS        := $(SRCS:.c=.o)

INCLUDE        :=      -I include/philosp\


.c.o:
	${CC} ${FLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

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

${NAME}:	${OBJS} 
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} ${INCLUDE} -o ${NAME} ${OBJS}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re


