/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:23:56 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/17 23:10:12 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_open_all(t_parser **lst)
{
	
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
		if (!arg)
			return (NULL);
		i = 0;
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
			//ft_open_all(&lst);
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
						if (infile != 0)
							close(infile);
						infile = open(lst->value, O_RDONLY);
						if (lst)
							lst = lst->next;
					}
				}
				else if (lst->type == REDIR_OUT)
				{
					lst = lst->next;
					if (lst && lst->type == WHITE_SPACE)
						lst = lst->next;
					if (lst && lst->type == WORD)
					{
						if (oufile != 1)
							close(oufile);
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
						if (oufile != 1)
							close(oufile);
						oufile = open(lst->value, O_WRONLY | O_CREAT | O_APPEND,
								0644);
						if (lst)
							lst = lst->next;
					}
				}
			}
		}
		arg[i] = NULL;
		if (!*arg)
			ft_cmdadd_back(&new, ft_cmdnew("", arg, infile, oufile));
		else
			ft_cmdadd_back(&new, ft_cmdnew(arg[0], arg, infile, oufile));
		infile = 0;
		oufile = 1;
		if (lst)
			lst = lst->next;
	}
	return (new);
}
