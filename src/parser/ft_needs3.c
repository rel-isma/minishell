/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 01:57:30 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/18 03:14:57 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_open_redir_out(t_parser **lst, int *oufile)
{
	if ((*lst) && (*lst)->type == REDIR_OUT)
	{
		(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WHITE_SPACE)
			(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WORD)
		{
			if (*oufile != 1)
				close(*oufile);
			*oufile = open((*lst)->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if ((*lst))
				(*lst) = (*lst)->next;
		}
	}
}

void	ft_open_redir_in(t_parser **lst, int *infile)
{
	if ((*lst) && (*lst)->type == REDIR_IN)
	{
		(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WHITE_SPACE)
			(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WORD)
		{
			if (*infile != 0)
				close(*infile);
			*infile = open((*lst)->value, O_RDONLY);
			if ((*lst))
				(*lst) = (*lst)->next;
		}
	}
}

void	ft_open_dredir_out(t_parser **lst, int *oufile)
{
	if ((*lst) && (*lst)->type == DREDIR_OUT)
	{
		(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WHITE_SPACE)
			(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WORD)
		{
			if (*oufile != 1)
				close(*oufile);
			*oufile = open((*lst)->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if ((*lst))
				(*lst) = (*lst)->next;
		}
	}
}

void	ft_delimiter(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line && ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	ft_open_here_doc(t_parser **lst, int *infile)
{
	char	*delimiter;
	int		fd;

	if ((*lst) && (*lst)->type == HERE_DOC)
	{
		(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WHITE_SPACE)
			(*lst) = (*lst)->next;
		if ((*lst))
		{
			delimiter = ft_strdup((*lst)->value);
			if (delimiter)
			{
				fd = open(".here_doc_temp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
				ft_delimiter(fd, delimiter);
				close(fd);
				*infile = open(".here_doc_temp", O_RDONLY);
				free(delimiter);
			}
		}
	}
}
