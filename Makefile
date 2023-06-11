# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 17:16:54 by rel-isma          #+#    #+#              #
#    Updated: 2023/06/11 19:06:55 by rel-isma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -L/usr/local/opt/readline/lib -lreadline

SOURCES = main.c

OBJECTS = $(SOURCES:%.c=obj/%.o)

LIBFT_PATH = ./libft
LIBFT_NAME = ft


NAME = minishell

all: libft $(NAME)

libft:
	make -C $(LIBFT_PATH)

obj/%.o: src/%.c src/minishell.h | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir obj

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
