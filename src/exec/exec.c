/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:44 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/19 02:39:05 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_builting(t_list *tmp)
{
	if (ft_strcmp(((t_cmd *)(tmp->content))->cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(((t_cmd *)(tmp->content))->cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(((t_cmd *)(tmp->content))->cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(((t_cmd *)(tmp->content))->cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(((t_cmd *)(tmp->content))->cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(((t_cmd *)(tmp->content))->cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(((t_cmd *)(tmp->content))->cmd, "env") == 0)
		return (1);
	return (0);
}

void	ft_exec(t_list *tmp)
{
	t_list	*tp;

	tp = tmp;
	if (ft_check_builting(tmp) && !((t_cmd *)(tmp->next)))
	{
		if (((t_cmd *)(tmp->content))->infile != -1)
			ft_builting(tmp);
	}
	else
		ft_commands(tmp);
}
