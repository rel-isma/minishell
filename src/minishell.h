/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:18:02 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/13 06:10:18 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>

typedef enum s_tokenstatus
{
	GENERAL = 1,
	IN_QUOTE,
	IN_DQUOTE,
}	t_status;

typedef enum s_tokentype
{
	WORD = 1,
	WHITE_SPACE,
	NEW_LINE,
	QOUTE,
	DOUBLE_QUOTE,
	ENV,
	PIPE_LINE,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	DREDIR_OUT,
}	t_type;

typedef struct s_lexer
{
	t_type			type;
	t_status		status;
	char			*value;
	struct s_lexer	*next;
}	t_lexer;

char	*ft_lexer(char *line);
t_lexer	*ft_lexernew(char *content, t_status status, t_type type);
void	ft_lexeradd_back(t_lexer **lst, t_lexer *new);
void	handle_redirection(t_lexer **tokenlist,
			char *line, int *i, t_status *s);
void	handle_special_characters(t_lexer **tokenlist,
			char *line, int *i, t_status *s);
void	handle_double_quote(t_lexer **tokenlist,
			char *line, int *i, t_status *s);
void	handle_quote(t_lexer **tokenlist,
			char *line, int *i, t_status *s);
void	handle_env(t_lexer **tokenlist,
			char *line, int *i, t_status *s);
void	handle_word(t_lexer **tokenlist,
			char *line, int *i, t_status *s);
int		ft_line_word(char *str);
int		ft_line_word(char *str);
void	ft_free_list(t_lexer *list);

#endif
