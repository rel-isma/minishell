# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 17:16:54 by rel-isma          #+#    #+#              #
#    Updated: 2023/08/28 00:11:18 by rel-isma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS =  -Wall -Wextra -Werror

LIBS = -lreadline -L ~/.brew/opt/readline/lib

SOURCES = src/main.c  src/needs_main.c src/sig_handler.c src/lexer/lexer.c src/lexer/lexer_needs.c  src/lexer/lexer_needs2.c \
          src/lexer/ft_free_all.c  src/lexer/lexer_needs_3.c src/syntax_errors/ft_syntax_errors.c src/syntax_errors/ft_check_stx_pipe.c \
		  src/syntax_errors/ft_check_stx_qoute.c src/syntax_errors/ft_check_stx_redir.c \
		  src/expander/ft_expander.c src/expander/ft_needs_exp.c src/expander/ft_needs_exp2.c \
		  src/parser/ft_join_argms.c  src/parser/ft_needs.c src/parser/ft_delele_dqu_qu.c src/parser/ft_join_cmd.c \
		  src/parser/ft_needs2.c src/parser/ft_needs3.c src/parser/ft_needs4.c \
		  src/exec/builting.c src/exec/exec.c  src/exec/commands.c src/exec/sort_list.c src/exec/ft_export.c\
		  src/exec/ft_cd.c src/exec/ft_env_pwd.c src/exec/ft_echo.c src/exec/ft_needs_cmds.c \
		  src/exec/ft_unset.c src/exec/needs_export.c \
		  src/exec/ft_exit.c src/exec/ft_cd_extra.c src/exec/needs_cmds1.c 

OBJECTS = $(SOURCES:%.c=obj/%.o)

LIBFT_PATH = ./libfc
LIBFT_NAME = ft

NAME = minishell

all: libft $(NAME)

libft:
	@make -C $(LIBFT_PATH)

obj/%.o: %.c src/minishell.h | obj
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include
	@printf "\033[0;36mCompiling $<\033[0m\n"

obj:
	@mkdir  -p obj/src/lexer obj/src/syntax_errors obj/src/expander obj/src/parser obj/src/exec

$(NAME): $(OBJECTS)
	@printf "\033[0;32mLinking...\033[0m\n"
	@$(CC) $(CFLAGS) $(LIBS) -L$(LIBFT_PATH) -l$(LIBFT_NAME) $(OBJECTS) -o $(NAME)
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

