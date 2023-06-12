# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 17:16:54 by rel-isma          #+#    #+#              #
#    Updated: 2023/06/12 15:35:14 by rel-isma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror 
LIBS = -lreadline #-L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include

SOURCES = src/main.c src/lexer/lexer.c src/lexer/lexer_needs.c

OBJECTS = $(SOURCES:%.c=obj/%.o)

LIBFT_PATH = ./libft
LIBFT_NAME = ft


NAME = minishell

all: libft $(NAME)

libft:
	make -C $(LIBFT_PATH)

obj/%.o: %.c src/minishell.h | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir obj
	mkdir obj/src
	mkdir obj/src/lexer

$(NAME): $(OBJECTS)
	$(CC) $(LIBS) -L$(LIBFT_PATH) -l$(LIBFT_NAME) $(OBJECTS) -o $(NAME)

clean:
	@make clean -C $(LIBFT_PATH)
	@printf "\e[32m removing obj\n"
	@rm -rf obj
	@printf "\e[0m"

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@printf "\e[32m removing executable\n"
	@rm -rf $(NAME)
	@printf "\e[0m"

re: fclean all

.PHONY: all clean fclean re libft
