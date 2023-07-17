/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:23:56 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/17 03:01:49 by rel-isma         ###   ########.fr       */
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
t_cmd	*ft_join_cmd(t_parser *lst)
{
	t_cmd	*new;
	char	**arg;
	int		i;
	int		infile;
	int		oufile;

	new = NULL;
	infile = 0;
	oufile = 1;
	while (lst)
	{
		arg = malloc((ft_len(lst) + 1) * sizeof(char *));
		i = 0;
		if (!arg)
			return (NULL);
		while (lst && lst->type != PIPE_LINE)
		{
			if (lst->type == WORD)
			{
				arg[i] = lst->value;
				i++;
				lst = lst->next;
			}
			if (lst && lst->type == WHITE_SPACE)
				lst = lst->next;
			if (lst && (lst->type == REDIR_IN || lst->type == REDIR_OUT
					|| lst->type == HERE_DOC || lst->type == DREDIR_OUT))
			{
				if (lst->type == REDIR_IN)
				{
					lst = lst->next;
					if (lst && lst->type == WHITE_SPACE)
						lst = lst->next;
					if (lst && lst->type == WORD)
					{
						infile = open(lst->value, O_RDONLY);
						if (lst)
							lst = lst->next;
					}
				}
				else if (lst->type == REDIR_OUT)
				{
                    close(oufile);
					lst = lst->next;
					if (lst && lst->type == WHITE_SPACE)
						lst = lst->next;
					if (lst && lst->type == WORD)
					{
						oufile = open(lst->value, O_WRONLY | O_CREAT | O_TRUNC,
							0644);
						if (lst)
							lst = lst->next;
					}
				}
				else if (lst->type == HERE_DOC)
				{
					
					if (lst)
						lst = lst->next;
				}
				else if (lst->type == DREDIR_OUT)
				{
					lst = lst->next;
					if (lst && lst->type == WHITE_SPACE)
						lst = lst->next;
					if (lst && lst->type == WORD)
					{
						oufile = open(lst->value, O_WRONLY | O_CREAT | O_APPEND,
							0644);
						if (lst)
							lst = lst->next;
					}
				}
			}
		}
		arg[i] = NULL;
		ft_cmdadd_back(&new, ft_cmdnew(arg[0], arg, infile, oufile));
		infile = 0;
		oufile = 1;
		if (lst)
			lst = lst->next;
	}
	return (new);
}
