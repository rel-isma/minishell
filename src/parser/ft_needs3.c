/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 01:57:30 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/27 18:12:38 by rel-isma         ###   ########.fr       */
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

void	ft_delimiter(int fd, t_parser *delimiter, char **env, char str)
{
	char	*line;
	t_lexer	*cur;
	t_lexer	*tmp;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (line && ft_strcmp(line, delimiter->value) == 0)
		{
			free(line);
			break ;
		}
		tmp = ft_lexer(line);
		if (str != '\"' && str != '\'')
			ft_expander(tmp, env, 0);
		cur = tmp;
		while (cur)
		{
			write(fd, cur->value, ft_strlen(cur->value));
			cur = cur->next;
		}
		write(fd, "\n", 1);
		ft_free_list(tmp);
	}
}

void	ft_open_here_doc(t_parser **lst, int *infile, char **env, char str1)
{
	static int	i = 1;
	int			fd;
	char		*str;

	if ((*lst) && (*lst)->type == HERE_DOC)
	{
		*infile = 0;
		str = ft_strjoin("heredoc>", ft_itoa(i));
		i++;
		(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WHITE_SPACE)
			(*lst) = (*lst)->next;
		if ((*lst))
		{
			if ((*lst)->value)
			{
				fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				ft_delimiter(fd, (*lst), env, str1);
				if (*infile != 0)
				{
					unlink(str);
					close(fd);
				}
				else
					*infile = open(str, O_RDONLY);
				(*lst) = (*lst)->next;
			}
		}
		free(str);
	}
}
