# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 17:16:54 by rel-isma          #+#    #+#              #
#    Updated: 2023/06/13 06:28:41 by rel-isma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror 
LIBS = -lreadline -L/Users/rel-isma/.brew/opt/readline/lib -I/Users/rel-isma/.brew/opt/readline/include

SOURCES = src/main.c src/lexer/lexer.c src/lexer/lexer_needs.c  src/lexer/lexer_needs2.c \
			src/lexer/ft_free_all.c

OBJECTS = $(SOURCES:%.c=obj/%.o)

LIBFT_PATH = ./libft
LIBFT_NAME = ft


NAME = minishell

all: libft $(NAME)

libft:
	@make -C $(LIBFT_PATH)

obj/%.o: %.c src/minishell.h | obj
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $<

obj:
	@mkdir obj
	@mkdir obj/src
	@mkdir obj/src/lexer

$(NAME): $(OBJECTS)
	@$(CC) $(LIBS) -L$(LIBFT_PATH) -l$(LIBFT_NAME) $(OBJECTS) -o $(NAME)
	@printf "\e[32m DONE 👌\n"

clean:
	@make clean -C $(LIBFT_PATH)
	@printf "\e[31m removing obj\n"
	@rm -rf obj

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@printf "\e[31m removing executable\n"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
