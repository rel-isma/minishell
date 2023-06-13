# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 17:16:54 by rel-isma          #+#    #+#              #
#    Updated: 2023/06/13 22:41:39 by rel-isma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror 
LIBS = -lreadline -L/Users/rel-isma/.brew/opt/readline/lib -I/Users/rel-isma/.brew/opt/readline/include

SOURCES = src/main.c src/lexer/lexer.c src/lexer/lexer_needs.c  src/lexer/lexer_needs2.c \
          src/lexer/ft_free_all.c  src/lexer/lexer_needs_3.c

OBJECTS = $(SOURCES:%.c=obj/%.o)

LIBFT_PATH = ./libft
LIBFT_NAME = ft

NAME = minishell

all: libft $(NAME)

libft:
	@make -C $(LIBFT_PATH)

obj/%.o: %.c src/minishell.h | obj
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;36mCompiled $<\033[0m\n"

obj:
	@mkdir -p obj/src/lexer

$(NAME): $(OBJECTS)
	@printf "\033[0;32mLinking...\033[0m\n"
	@$(CC) $(LIBS) -L$(LIBFT_PATH) -l$(LIBFT_NAME) $(OBJECTS) -o $(NAME)
	@printf "\033[0;32m$(NAME) compilation completed.\033[0m\n"

clean:
	@make clean -C $(LIBFT_PATH)
	@printf "\033[0;31mCleaning object files...\033[0m\n"
	@rm -rf obj
	@printf "\033[0;32mObject files cleaned.\033[0m\n"

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@printf "\033[0;31mCleaning executable...\033[0m\n"
	@rm -f $(NAME)
	@printf "\033[0;32mExecutable cleaned.\033[0m\n"

re: fclean all

.PHONY: all clean fclean re libft

