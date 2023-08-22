/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:23:56 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/22 23:57:16 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_open_all(t_parser **lst, t_cmd *cmd, char str)
{
	char	*ir;

	ir = NULL;
	if (*lst && ((*lst)->type == REDIR_IN || (*lst)->type == REDIR_OUT
			|| (*lst)->type == HERE_DOC || (*lst)->type == DREDIR_OUT))
	{
		ft_open_redir_out(lst, cmd);
		ft_open_redir_in(lst, cmd);
		ft_open_here_doc(lst, cmd, str, ir);
		ft_open_dredir_out(lst, cmd);
	}
}

void	ft_creat_cmd_arg(t_parser **lst, t_cmd *cmd, char str)
{
	int	i;

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
		ft_open_all(lst, cmd, str);
	}
	cmd->argms[i] = NULL;
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
		ft_creat_cmd_arg(&lst, cmd, str);
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
