/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 08:08:24 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/15 08:09:11 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_open_redir_out(t_parser **lst, t_cmd *cmd)
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
			if (open((*lst)->value, O_WRONLY | O_CREAT | O_TRUNC, 0644) == -1)
			{
				ft_putstr_fd("minsihell :", 2);
				perror((*lst)->value);
			}
			cmd->oufilename = (*lst)->value;
			if ((*lst))
				(*lst) = (*lst)->next;
		}
	}
}

void	ft_open_redir_in(t_parser **lst, t_cmd *cmd)
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
			if (cmd->infile < 0)
			{
				printf("minishell: %s: No such file or directory\n",
					(*lst)->value);
				g_minishell.exit_code = 1;
			}
			cmd->infilename = (*lst)->value;
			if ((*lst))
				(*lst) = (*lst)->next;
		}
	}
}

void	ft_open_dredir_out(t_parser **lst, t_cmd *cmd)
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
			cmd->oufilename = (*lst)->value;
			if ((*lst))
				(*lst) = (*lst)->next;
		}
	}
}
