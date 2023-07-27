/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:18:02 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/27 01:10:09 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libfc/libft.h"
# include <fcntl.h>
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
	VOID,
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

typedef struct s_exp
{
	char			*key;
	char			*vl;
	int				len1;
	int				len2;
}					t_exp;

typedef struct s_parser
{
	t_type			type;
	char			*value;
	struct s_parser	*next;
}					t_parser;

typedef struct s_cmd
{
	char			*cmd;
	char			**argms;
	int				infile;
	int				oufile;
	struct s_cmd	*next;
}					t_cmd;

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
void				ft_handle_white_space(t_lexer **tokenlist, char *line,
						int *i, t_status s);
int					ft_line_word(char *str);
int					ft_line_env(char *str);
int					white_space(char str);
void				ft_free_list(t_lexer *list);

//////functions syntax_errors ////////////////////////

int					ft_syntax_errors(t_lexer *token_lst);
int					ft_check_syntax_qoute(t_lexer *lst);
int					ft_check_stx_redir_out(t_lexer *cur);
int					ft_check_stx_redir_in(t_lexer *cur);
int					ft_check_stx_apend(t_lexer *cur);
int					ft_check_stx_heredoc(t_lexer *cur);
int					ft_check_syntax_pipe(t_lexer *cur);

//////functions expander ////////////////////////

t_expand			*ft_lexernew_expnd(char *key_v, char *val);
void				ft_lexeradd_back_expnd(t_expand **lst, t_expand *new);
void				ft_expander(t_lexer *lst, char **env, int flg);
t_expand			*ft_init_expander(char **env);
void				ft_free_list_exp(t_expand *list);
int					ft_strlen_env_aftr(char *env);
int					ft_strlen_env_befor(char *env);
void				ft_free_list_exp(t_expand *list);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_expand_valid(t_expand *cur, t_lexer *tmp, int flg);
void				ft_expand_no_valid(t_lexer *tmp, char *str);
void				ft_check_after_here_doc(t_lexer **tmp);

/////////// functions parser ////////////////

t_parser			*ft_parsernew(char *content, int flg, t_type type);
void				ft_parseradd_back(t_parser **lst, t_parser *new);
int					check_no_word(t_lexer *lst);
t_parser			*ft_join_word(t_lexer *cur);
t_cmd				*ft_join_argms(t_lexer **lst, char **env);
void				ft_delete_double_quote(t_lexer **lst);
void				ft_delete_quote(t_lexer **lst);
void				ft_free_list_cmd(t_cmd *list);
t_cmd				*ft_join_cmd(t_parser *lst, char **env, char str);
t_cmd				*ft_cmdnew(char *cmd, char **args, int infile, int oufile);
void				ft_cmdadd_back(t_cmd **lst, t_cmd *new);
int					ft_len(t_parser *cur);
void				ft_open_all(t_parser **lst, int *infile, int *oufile, char **env, char str);
void				ft_open_redir_out(t_parser **lst, int *oufile);
void				ft_open_redir_in(t_parser **lst, int *infile);
void				ft_open_dredir_out(t_parser **lst, int *oufile);
void				ft_open_here_doc(t_parser **lst, int *infile, char **env, char str);
void				ft_free_list_join(t_parser *list);

#endif
