/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:37 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/18 18:35:29 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builting(t_list *tmp)
{
	static int	flg;

	flg = 0;
	if (ft_strcmp((tl(tmp->content))->cmd, "echo") == 0)
		return (g_minishell.exit_code = ft_echo(tmp), 1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "pwd") == 0)
		return (g_minishell.exit_code = ft_pwd(), 1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "cd") == 0)
		return (g_minishell.exit_code = ft_cd(tmp), 1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "unset") == 0)
		return (g_minishell.exit_code = ft_unset(tmp), 1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "env") == 0)
		return (g_minishell.exit_code 
			= ft_env((tl(tmp->content))->envl, tmp), 1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "export") == 0)
		return (g_minishell.exit_code = ft_export(tmp, &flg), 1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "exit") == 0)
		return (g_minishell.exit_code = ft_exit_builtin(tmp), 1);
	return (0);
}
