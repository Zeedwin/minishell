#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := minishell
CC        := gcc
FLAGS    := -Wall -Wextra -Werror -g -I ${HOME}/.brew/Cellar/readline/8.2.1/include
LDFLAGS :=  -lreadline -fsanitize=address -L ${HOME}/.brew/Cellar/readline/8.2.1/lib -lreadline -L ${HOME}/.brew/Cellar/readline/8.2.1/lib -lhistory
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS		:=            parsing/error.c \
						  parsing/ft_itoa.c \
						  parsing/var_dollard.c \
						  parsing/ft_strstr.c \
						  parsing/ft_strcmp.c \
						  parsing/tokenizer.c \
						  parsing/lexeur1.c \
						  parsing/find_path.c \
                          parsing/ft_putstr.c \
                          parsing/ft_split.c \
                          parsing/ft_strcpy.c \
                          parsing/ft_strjoin.c \
                          parsing/ft_strncmp.c \
                          parsing/main.c \
                          parsing/pathrefresh.c \
						  parsing/ft_strtrim.c \
						  parsing/ft_strchr.c \
						  parsing/ft_substr.c \
						  parsing/ft_strlcpy.c \
						  built-ins/cd.c \
						  built-ins/exit.c \
						  built-ins/pwd.c \
						  built-ins/echo.c \
						  parsing/ft_strnstr.c \
						  parsing/ft_strdup.c \
						  parsing/testeur.c \
						  parsing/exe.c \
						  parsing/free.c \
						  #parsing/tokenodes.c \
                          #parsing/test.c \
                          #parsing/∞shell.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

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
			${CC} ${FLAGS} -o ${NAME} ${OBJS} ${LDFLAGS}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME} $(READLINE_PATH)

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

readline: $(READLINE_PATH)
 
 $(READLINE_PATH):
	sh ./install_readline.sh

re:			fclean all

.PHONY:		all clean fclean re