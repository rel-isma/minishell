/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:18:02 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/27 19:36:39 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libfc/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
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

typedef struct s_global
{
	char			d_s;
	int				www;
	int				err;
	int				env;
	int				stop_exection;
	int				stdin_backup;
	int				heredoc_executing;
	t_expand		*envl;
	int				command_executing;
	int				exit_code;
	char			**here;
	char			*str;
	char			*cmd;
}					t_global;

t_global			g_minishell;

typedef struct s_cmd
{
	char			*cmd;
	char			**argms;
	int				type;
	char			*path;
	int				infile;
	int				oufile;
	char			*infilename;
	char			*oufilename;
	t_expand		*envl;
	int				exit_status;
	char			*pwd;
	char			*pwd1;
	int				lvl;
}					t_cmd;

///////////////////////// functions lexer /////////////////////////////////////

t_lexer				*ft_lexer(char *line);
int					white_space(char str);
t_lexer				*ft_lexernew(char *content, t_status status, t_type type);
void				ft_l_back(t_lexer **lst, t_lexer *new);
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
void				ft_free_lexer(t_lexer *list);

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
void				ft_l_back_expnd(t_expand **lst, t_expand *new);
void				ft_expander(t_lexer *lst, t_expand *exp, int flg);
t_expand			*ft_init_expander(char **env);
void				ft_free_list_exp(t_expand *list);
int					ft_strlen_env_aftr(char *env, int *flg);
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
t_parser			*ft_join_word(t_lexer *cur, int flg);
t_list				*ft_join_argms(t_lexer **lst, t_expand *env);
void				ft_delete_double_quote(t_lexer **lst);
void				ft_delete_quote(t_lexer **lst);
void				ft_free_list_cmd(t_cmd *list);
t_list				*ft_join_cmd(t_parser *lst, t_expand *env, char str);
t_cmd				*ft_cmdnew(char *cmd, char **args, int infile, int oufile);
void				ft_cmdadd_back(t_cmd **lst, t_cmd *new);
int					ft_len(t_parser *cur);
void				ft_open_all(t_parser **lst, t_cmd *cmd, char str);
void				ft_open_redir_out(t_parser **lst, t_cmd *cmd);
void				ft_open_redir_in(t_parser **lst, t_cmd *cmd);
void				ft_open_dredir_out(t_parser **lst, t_cmd *cmd);
void				ft_open_here_doc(t_parser **lst, t_cmd *cmd, char str,
						char *ir);
void				ft_free_list_join(t_parser *list);

/////////////////// exec //////////////////////////////

int					ft_builting(t_list *tmp);
void				ft_exec(t_list *tmp);
void				ft_commands(t_list *tmp);
void				sort_list(t_expand *pp);
int					ft_exec_cmd(t_list *cmd, int *fd, int old_fd);
int					ft_check_builting(t_list *tmp);
void				ft_free_tab(char **env);
int					ft_check_duble(char *key, char *vl, t_expand *env, int flg);
int					syntax_export(char *str);
void				ft_print_export(t_list *tmp, int flg, t_expand *p);
int					ft_export(t_list *tmp, int *flg1);
int					ft_cd(t_list *tmp);
int					ft_unset(t_list *tmp);
void				ft_env(t_expand *pp, t_list *tmp, int flg);
int					ft_pwd(t_list *tmp);
int					ft_echo(t_list *tmp);
char				**ft_get_env_tab(t_list *cmd);
char				*ft_get_path(t_list *cmd);
int					ft_exit_builtin(t_list *tmp);
void				pwd_old(char *pwd, char *old_pwd, t_list *tmp);
int					valid_home(t_list *tmp);
void				cd_home(t_list *tmp);
int					cd_root(char *str);
void				ft_open_redir_out(t_parser **lst, t_cmd *cmd);
void				ft_open_redir_in(t_parser **lst, t_cmd *cmd);
void				ft_open_dredir_out(t_parser **lst, t_cmd *cmd);
void				ft_exeve_in_minishell(t_list *cmd, char **env);
void				ft_exec_in_child(t_list *cmd, char **env, int *fd,
						int old_fd);
void				ft_free_tab(char **env);
void				command_not_found(char *str);
void				close_all_fds(t_list *cmd);
t_expand			*copy_list(t_expand *head);
void				free_list(t_expand *head);
int					ft_check_argms(int ac, char **av);
void				ft_free_all_minishell(t_list *cmds);
void				close_all_fds(t_list *cmd);
void				sig_handler(int signum);
void				ft_shlvl(t_expand *envl);
int					cd_error(t_list *tmp);
void				printf_msg(char *str, char *cmd);
#endif
