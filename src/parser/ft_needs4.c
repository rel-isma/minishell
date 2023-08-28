/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 08:08:24 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/28 15:54:20 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_redir_out(t_parser **lst, t_cmd *cmd, char **p_erro)
{
	if ((*lst) && (*lst)->type == REDIR_OUT)
	{
		(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WHITE_SPACE)
			(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WORD)
		{
			if (cmd->oufile != 1)
				close(cmd->oufile);
			cmd->oufile = open((*lst)->value, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (cmd->oufile < 0 && g_minishell.stop_exection == 0)
			{
				g_minishell.exit_code = 1;
				cmd->check_ero = 1;
				if (!*p_erro)
					*p_erro = (*lst)->value;
				(*lst) = (*lst)->next;
				return (1);
			}
			cmd->oufilename = (*lst)->value;
			if ((*lst))
				(*lst) = (*lst)->next;
		}
	}
	return (1);
}

int	ft_open_redir_in(t_parser **lst, t_cmd *cmd, char **p_erro)
{
	if ((*lst) && (*lst)->type == REDIR_IN)
	{
		(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WHITE_SPACE)
			(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WORD)
		{
			if (cmd->infile != 0)
				close(cmd->infile);
			cmd->infile = open((*lst)->value, O_RDONLY);
			if (cmd->infile < 0 && g_minishell.stop_exection == 0)
			{
				g_minishell.exit_code = 1;
				cmd->check_ero = 1;
				if (!*p_erro)
					*p_erro = (*lst)->value;
				(*lst) = (*lst)->next;
				return (1);
			}
			if (cmd->infilename && ft_strncmp(cmd->infilename, "/tmp/.heredoc>", 14) == 0)
				free(cmd->infilename);
			cmd->infilename = (*lst)->value;
			if ((*lst))
				(*lst) = (*lst)->next;
		}
	}
	return (1);
}

int	ft_open_dredir_out(t_parser **lst, t_cmd *cmd, char **p_erro)
{
	if ((*lst) && (*lst)->type == DREDIR_OUT)
	{
		(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WHITE_SPACE)
			(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WORD)
		{
			if (cmd->oufile != 1)
				close(cmd->oufile);
			cmd->oufile = open((*lst)->value, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (cmd->oufile < 0)
			{
				g_minishell.exit_code = 1;
				cmd->check_ero = 1;
				if (!*p_erro)
					*p_erro = (*lst)->value;
				(*lst) = (*lst)->next;
				return (1);
			}
			cmd->oufilename = (*lst)->value;
			if ((*lst))
				(*lst) = (*lst)->next;
		}
	}
	return (1);
}
