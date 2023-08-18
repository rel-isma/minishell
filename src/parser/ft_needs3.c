/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 01:57:30 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/18 21:44:49 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_in_file(t_lexer *cur, int fd)
{
	while (cur)
	{
		write(fd, cur->value, ft_strlen(cur->value));
		cur = cur->next;
	}
	write(fd, "\n", 1);
}

void	ft_delimiter(int fd, t_parser *delimiter, t_expand *env, char str)
{
	char	*line;
	t_lexer	*tmp;

	while (1)
	{
		g_minishell.heredoc_executing = 1;
		line = readline("> ");
		if (!line)
		{
			break ;
		}
		if (line && ft_strcmp(line, delimiter->value) == 0)
		{
			free(line);
			break ;
		}
		tmp = ft_lexer(line);
		if (str != '\"' && str != '\'')
			ft_expander(tmp, env, 0);
		ft_print_in_file(tmp, fd);
		ft_free_lexer(tmp);
	}
	g_minishell.heredoc_executing = 0;
}

void	ft_open_here_doc(t_parser **lst, t_cmd *cmd, char str1)
{
	static int	i;
	int			fd;
	char		*str;

	i = 1;
	if ((*lst) && (*lst)->type == HERE_DOC)
	{
		str = ft_strjoin("/tmp/.heredoc>", ft_itoa(i));
		// ft_itoa;
		// return (perror("malloc"), exit(EXIT_FAILURE), NULL);
		i++;
		(*lst) = (*lst)->next;
		if ((*lst) && (*lst)->type == WHITE_SPACE)
			(*lst) = (*lst)->next;
		if ((*lst))
		{
			if ((*lst)->value)
			{
				fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				ft_delimiter(fd, (*lst), cmd->envl, str1);
				cmd->infilename = str;
				close(fd);
				(*lst) = (*lst)->next;
			}
		}
	}
}
