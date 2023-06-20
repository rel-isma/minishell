/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:18:02 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/21 00:08:29 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libfc/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef enum s_tokenstatus
{
	GENERAL = 1,
	IN_QUOTE,
	IN_DQUOTE,
}					t_status;

typedef enum s_tokentype
{
	WORD = 1,
	WHITE_SPACE,
	QOUTE,
	DOUBLE_QUOTE,
	ENV,
	PIPE_LINE,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	DREDIR_OUT,
}					t_type;

typedef struct s_expand
{
	char			*key;
	char			*value;
	struct s_expand	*next;
}					t_expand;

typedef struct s_lexer
{
	t_type			type;
	t_status		status;
	char			*value;
	struct s_lexer	*next;
}					t_lexer;

///////////////////////// functions lexer /////////////////////////////////////

t_lexer				*ft_lexer(char *line);
t_lexer				*ft_lexernew(char *content, t_status status, t_type type);
void				ft_lexeradd_back(t_lexer **lst, t_lexer *new);
void				handle_redirection(t_lexer **tokenlist, char *line, int *i,
						t_status *s);
void				handle_special_characters(t_lexer **tokenlist, char *line,
						int *i, t_status *s);
void				special_variables_1(t_lexer **tokenlist, char *line, int *i,
						t_status *s);
void				special_variables_2(t_lexer **tokenlist, char *line, int *i,
						t_status *s);
void				handle_double_quote(t_lexer **tokenlist, char *line, int *i,
						t_status *s);
void				handle_quote(t_lexer **tokenlist, char *line, int *i,
						t_status *s);
void				handle_env(t_lexer **tokenlist, char *line, int *i,
						t_status *s);
void				handle_word(t_lexer **tokenlist, char *line, int *i,
						t_status *s);
int					ft_line_word(char *str);
int					ft_line_word(char *str);
int					ft_line_env(char *str);
void				ft_free_list(t_lexer *list);

//////functions syntax_errors ////////////////////////

void				ft_syntax_errors(t_lexer *token_lst);
int					ft_check_syntax_qoute(t_lexer *lst);
int					ft_check_stx_redir_out(t_lexer *cur);
int					ft_check_stx_redir_in(t_lexer *cur);
int					ft_check_stx_apend(t_lexer *cur);
int					ft_check_stx_heredoc(t_lexer *cur);
int					ft_check_syntax_pipe(t_lexer *cur);

//////functions expander ////////////////////////

t_expand			*ft_lexernew_expnd(char *key_v, char *val);
void				ft_lexeradd_back_expnd(t_expand **lst, t_expand *new);
t_expand			*ft_expander(t_lexer *lst, char **env);
void				ft_free_list_exp(t_expand *list);
int					ft_strlen_env_aftr(char *env);
int					ft_strlen_env_befor(char *env);
void				ft_free_list_exp(t_expand *list);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_expand_valid(t_expand *cur, t_lexer *tmp);
void				ft_expand_no_valid(t_lexer *tmp, char *str);
void				ft_check_after_here_doc(t_lexer **tmp);

#endif
