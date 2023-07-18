# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 17:16:54 by rel-isma          #+#    #+#              #
#    Updated: 2023/07/18 01:59:43 by rel-isma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
LIBS = -lreadline -L/Users/rel-isma/.brew/opt/readline/lib -I/Users/rel-isma/.brew/opt/readline/include

SOURCES = src/main.c src/lexer/lexer.c src/lexer/lexer_needs.c  src/lexer/lexer_needs2.c \
          src/lexer/ft_free_all.c  src/lexer/lexer_needs_3.c src/syntax_errors/ft_syntax_errors.c src/syntax_errors/ft_check_stx_pipe.c \
		  src/syntax_errors/ft_check_stx_qoute.c src/syntax_errors/ft_check_stx_redir.c \
		  src/expander/ft_expander.c src/expander/ft_needs_exp.c src/expander/ft_needs_exp2.c \
		  src/parser/ft_join_argms.c  src/parser/ft_needs.c src/parser/ft_delele_dqu_qu.c src/parser/ft_join_cmd.c \
		  src/parser/ft_needs2.c src/parser/ft_needs3.c

OBJECTS = $(SOURCES:%.c=obj/%.o)

LIBFT_PATH = ./libfc
LIBFT_NAME = ft

NAME = minishell

all: libft $(NAME)

libft:
	@make -C $(LIBFT_PATH)

obj/%.o: %.c src/minishell.h | obj
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;36mCompiling $<\033[0m\n"
	@sleep 0.5

obj:
	@mkdir  -p obj/src/lexer obj/src/syntax_errors obj/src/expander obj/src/parser

$(NAME): $(OBJECTS)
	@printf "\033[0;32mLinking...\033[0m\n"
	@sleep 0.5
	@$(CC) $(LIBS) -L$(LIBFT_PATH) -l$(LIBFT_NAME) $(OBJECTS) -o $(NAME)
	@printf "\033[0;32m$(NAME) compilation completed.\033[0m\n"

clean:
	@make clean -C $(LIBFT_PATH)
	@printf "\033[0;31mCleaning object files...\033[0m\n"
	@sleep 0.5
	@rm -rf obj
	@printf "\033[0;32mObject files cleaned.\033[0m\n"
	@sleep 0.5

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@printf "\033[0;31mCleaning executable...\033[0m\n"
	@sleep 0.5
	@rm -f $(NAME)
	@printf "\033[0;32mExecutable cleaned.\033[0m\n"

re: fclean all


.PHONY: all clean fclean re libft

