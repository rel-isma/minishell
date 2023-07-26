/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:41:38 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/17 21:46:25 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_cmdnew(char *cmd, char **args, int infile, int oufile)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->cmd = ft_strdup(cmd);
	node->argms = args;
	node->infile = infile;
	node->oufile = oufile;
	node->next = NULL;
	return (node);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->next = NULL;
}

int	ft_len(t_parser *cur)
{
	int	len;

	len = 0;
	if (cur && cur->type == PIPE_LINE)
		cur = cur->next;
	while (cur && cur->type != PIPE_LINE)
	{
		if (cur && (cur->type == REDIR_IN || cur->type == REDIR_OUT
				|| cur->type == HERE_DOC || cur->type == DREDIR_OUT))
		{
			cur = cur->next;
			if (cur && cur->type == WHITE_SPACE)
				cur = cur->next;
			if (cur && cur->type == WORD)
				cur = cur->next;
		}
		else if (cur && cur->type == WORD)
			len++;
		if (cur)
			cur = cur->next;
	}
	return (len);
}
