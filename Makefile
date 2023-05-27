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
FLAGS    := -Wall -Wextra -Werror -g -I/Users/$(USER)/homebrew/opt/readline/include
LDFLAGS :=  -lreadline -L/Users/$(USER)/homebrew/opt/readline/lib -lreadline -lhistory  -g #-fsanitize=address 
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS		:=    		  parsing/exe2.c \
						  parsing/var_dollard_1.c \
						  parsing/exe_gen2.c \
						  parsing/lexeur2.c \
						  parsing/cpytrichar.c \
						  parsing/exe_gen.c \
						  parsing/utils_6.c \
						  parsing/utils_5.c \
						  parsing/utils_4.c \
						  parsing/utils_3.c \
						  parsing/utils_2.c \
						  parsing/utils_1.c \
						  parsing/lexer2.c \
						  parsing/utils_lexer2.c \
						  parsing/utils_lexer.c \
						  parsing/count.c \
						  parsing/find_path1.c \
						  parsing/exe1.c \
						  parsing/pid.c	\
						  parsing/error.c \
						  parsing/ft_itoa.c \
						  parsing/var_dollard.c \
						  parsing/var_dollard2.c \
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
						  built-ins/env.c \
						  built-ins/echo.c \
						  built-ins/env2.c \
						  parsing/ft_strnstr.c \
						  parsing/ft_strdup.c \
						  parsing/testeur.c \
						  parsing/exe.c \
						  parsing/free.c \
						  parsing/ft_calloc.c\
						  parsing/ft_bzero.c\
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

