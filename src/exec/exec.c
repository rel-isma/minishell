/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:44 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/11 23:34:01 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_builting(t_list *tmp)
{
	if (ft_strcmp((tl(tmp->content))->cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "export") == 0)
		return (1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "env") == 0)
		return (1);
	return (0);
}
void	ft_exec(t_list *tmp)
{
	t_list	*tp;

	tp = tmp;
	if (ft_check_builting(tmp) && !(tl(tmp->next)))
	{
		if ((tl(tmp->content))->infile != -1)
			ft_builting(tmp);
	}
	else
		ft_commands(tmp);
}
