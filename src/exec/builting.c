/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:37 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/04 11:52:45 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	ft_exit_builtin(t_list *tmp) // finish fot exit builting
{
	printf("exit\n");
	exit((tl(tmp->content))->exit_status);
}


int	ft_builting(t_list *tmp) // not yet
{
	static int flg = 0;

	if (ft_strcmp((tl(tmp->content))->cmd, "echo") == 0)
		return (ft_echo(tmp));
	if (ft_strcmp((tl(tmp->content))->cmd, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp((tl(tmp->content))->cmd, "cd") == 0)
		return (ft_cd(tmp));
	if (ft_strcmp((tl(tmp->content))->cmd, "unset") == 0)
		return (ft_unset(tmp));
	if (ft_strcmp((tl(tmp->content))->cmd, "env") == 0)
		return (ft_env((tl(tmp->content))->envl, &flg));
	if (ft_strcmp((tl(tmp->content))->cmd, "export") == 0)
		return (ft_export(tmp, &flg));
	if (ft_strcmp((tl(tmp->content))->cmd, "exit") == 0)
		return (ft_exit_builtin(tmp));
	// if (ft_strcmp((tl(tmp->content))->cmd, "exit") == 0)
	// {
	// 	if (!(tl(tmp->content))->argms[1])
	// 		ft_exit_builtin(tmp);
	// }
	return 0;
}
