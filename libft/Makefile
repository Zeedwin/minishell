# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 16:33:52 by jgirard-          #+#    #+#              #
#    Updated: 2022/11/16 13:28:39 by jgirard-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= Libft.a
CC		= gcc
RM		= rm -rf
CFLAGS  = -Wall -Wextra -Werror
I_DIR 	= .
OBJ_DIR = obj

SRCS	= ft_isalpha.c		\
          ft_isdigit.c		\
          ft_isalnum.c		\
          ft_isascii.c		\
          ft_isprint.c		\
          ft_strlen.c		\
          ft_memset.c		\
          ft_bzero.c		\
          ft_memcpy.c		\
          ft_memmove.c		\
          ft_strlcpy.c		\
          ft_strlcat.c		\
          ft_toupper.c		\
          ft_tolower.c		\
          ft_strchr.c		\
          ft_strrchr.c		\
          ft_strncmp.c		\
          ft_memchr.c		\
          ft_memcmp.c		\
          ft_atoi.c			\
          ft_strnstr.c		\
          ft_calloc.c		\
          ft_strdup.c		\
          ft_memcmp.c		\
          ft_strtrim.c		\
          ft_substr.c		\
          ft_strjoin.c		\
          ft_strtrim.c		\
          ft_split.c		\
          ft_itoa.c			\
          ft_strmapi.c		\
          ft_striteri.c		\
          ft_putchar_fd.c 	\
          ft_putstr_fd.c 	\
          ft_putendl_fd.c 	\
          ft_putnbr_fd.c    \
          ft_abs.c	        
 
BONUS	= ft_lstnew_bonus.c 		\
          ft_lstadd_front_bonus.c 	\
          ft_lstsize_bonus.c 		\
          ft_lstlast_bonus.c 		\
          ft_lstadd_back_bonus.c 	\
          ft_lstdelone_bonus.c 		\
          ft_lstclear_bonus.c 		\
          ft_lstiter_bonus.c 		\
		  ft_lstmap_bonus.c			\
	

ifdef WITH_BONUS
	OBJ 		= $(BONUS:%.c=%.o)
	OBJ_PFX		=	$(addprefix $(OBJ_DIR)/, $(OBJ))
else
	OBJ			= $(SRCS:%.c=%.o)
	OBJ_PFX		=	$(addprefix $(OBJ_DIR)/, $(OBJ))
endif

all:    $(NAME)

$(NAME): $(OBJ_PFX)
	ar -rcs $(NAME) $(OBJ_PFX)
bonus:
	@make WITH_BONUS=1

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I$(I_DIR)
	
clean:
	$(RM) $(OBJ_DIR)
	
fclean:    clean
	$(RM) $(NAME)
 
re:    fclean all
 
.PHONY:    all clean fclean re bonus