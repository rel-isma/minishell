/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:23:56 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/28 15:53:48 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_all(t_parser **lst, t_cmd *cmd, char str, char **p_erro)
{
	char	*ir;

	ir = NULL;
	if (*lst && ((*lst)->type == REDIR_IN || (*lst)->type == REDIR_OUT
			|| (*lst)->type == HERE_DOC || (*lst)->type == DREDIR_OUT))
	{
		if (!ft_open_redir_out(lst, cmd, p_erro))
			return (0);
		if (!ft_open_redir_in(lst, cmd, p_erro))
			return (0);
		if (!ft_open_here_doc(lst, cmd, str, ir))
			return (1);
		if (!ft_open_dredir_out(lst, cmd, p_erro))
			return (0);
	}
	return (1);
}

void	print_erro_(char *p_erro)
{
	if (p_erro)
	{
		ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(p_erro, 2);
        ft_putstr_fd(": ", 2);
        if (access(p_erro, F_OK) == -1)
            ft_putstr_fd("No such file or directory\n", 2);
        else if (access(p_erro, X_OK | W_OK | R_OK) == -1)
            ft_putstr_fd("Permission denied\n", 2);
        else
            ft_putendl_fd(strerror(errno), 2);
        g_minishell.exit_code = 1;
	}

}

int	ft_creat_cmd_arg(t_parser **lst, t_cmd *cmd, char str)
{
	int	i;
	char	*p_erro;

	i = 0;
	while ((*lst) && (*lst)->type != PIPE_LINE)
	{
		if ((*lst)->type == WORD)
		{
			cmd->type = WORD;
			cmd->argms[i] = ft_strdup((*lst)->value);
			i++;
			(*lst) = (*lst)->next;
		}
		if ((*lst) && (*lst)->type == WHITE_SPACE)
		{
			cmd->type = WHITE_SPACE;
			(*lst) = (*lst)->next;
		}
		if (!ft_open_all(lst, cmd, str, &p_erro))
			return (0);
	}
	cmd->argms[i] = NULL;
	print_erro_(p_erro);
	return (1);
}

void	cmd_init(t_cmd *cmd, t_expand *env)
{
	cmd->argms = NULL;
	cmd->cmd = NULL;
	cmd->infile = 0;
	cmd->oufile = 1;
	cmd->type = 0;
	cmd->exit_status = 0;
	cmd->infilename = NULL;
	cmd->oufilename = NULL;
	cmd->check_ero = 0;
	cmd->envl = env;
}
t_list	*ft_join_cmd(t_parser *lst, t_expand *env, char str)
{
	t_list	*list;
	t_cmd	*cmd;

	list = NULL;
	cmd = NULL;
	while (lst)
	{
		cmd = malloc(sizeof(t_cmd));
		cmd_init(cmd, env);
		cmd->argms = malloc((ft_len(lst) + 1) * sizeof(char *));
		if (!cmd->argms)
			return (perror("malloc"), NULL);
		if (!ft_creat_cmd_arg(&lst, cmd, str))
		{
			free(cmd->argms);
			free(cmd);
			return (NULL);
		}
		if (!*(cmd->argms))
			cmd->cmd = ft_strdup("");
		else
			cmd->cmd = ft_strdup(cmd->argms[0]);
		ft_lstadd_back(&list, ft_lstnew(cmd));
		if (lst)
			lst = lst->next;
	}
	return (list);
}
