/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 01:57:30 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/07 10:18:32 by yoel-bas         ###   ########.fr       */
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
			cmd->oufile = open((*lst)->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(open((*lst)->value, O_WRONLY | O_CREAT | O_TRUNC, 0644) == - 1)
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
				printf("minishell: %s: No such file or directory\n", (*lst)->value);
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
			cmd->oufile = open((*lst)->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			cmd->oufilename = (*lst)->value;
			if ((*lst))
				(*lst) = (*lst)->next;
		}
	}
}

void	ft_delimiter(int fd, t_parser *delimiter, t_expand *env, char str)
{
	char	*line;
	t_lexer	*cur;
	t_lexer	*tmp;

	while (1)
	{
		g_minishell.heredoc_executing = 1;
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
		ft_free_lexer(tmp);
	}
	g_minishell.heredoc_executing = 0;
}

void	ft_open_here_doc(t_parser **lst, t_cmd *cmd, char str1)
{
	static int	i = 1;
	int			fd;
	char		*str;

	if ((*lst) && (*lst)->type == HERE_DOC)
	{
		str = ft_strjoin("/tmp/.heredoc>", ft_itoa(i));
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
