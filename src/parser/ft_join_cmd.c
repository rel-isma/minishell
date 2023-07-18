/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:23:56 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/18 02:08:13 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_creat_cmd_arg(t_parser **lst, int *infile, int *oufile, char **arg)
{
	int	i;

	i = 0;
	while ((*lst) && (*lst)->type != PIPE_LINE)
	{
		if ((*lst)->type == WORD)
		{
			arg[i] = ft_strdup((*lst)->value);
			i++;
			(*lst) = (*lst)->next;
		}
		if ((*lst) && (*lst)->type == WHITE_SPACE)
			(*lst) = (*lst)->next;
		ft_open_all(lst, infile, oufile);
	}
	arg[i] = NULL;
}

t_cmd	*ft_join_cmd(t_parser *lst)
{
	t_cmd	*new;
	char	**arg;
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
		ft_creat_cmd_arg(&lst, &infile, &oufile, arg);
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
