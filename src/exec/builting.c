/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:37 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/08 04:33:23 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit_builtin(t_list *tmp) // finish fot exit builting
{
	long long status;
	if ((tl(tmp->content))->argms[1])
	{
		if ((tl(tmp->content))->argms[2])
		{
			printf("exit\n");
			printf("minishell: exit: too many arguments\n");
			exit(g_minishell.exit_code);
		}
		if (strlen((tl(tmp->content))->argms[1]) > 20
			|| syntax_exit((tl(tmp->content))->argms[1]))
		{
			printf("exit\n");
			printf("minishell : exit: %s : numeric argument required\n",
				(tl(tmp->content))->argms[1]);
			g_minishell.exit_code = 255;
			exit(g_minishell.exit_code);
		}
		else
		{
			status = ft_atoi((tl(tmp->content))->argms[1]);
			if (status > 255)
			{
				status %= 256;
				g_minishell.exit_code = status;
			}
			else
				g_minishell.exit_code = status;
		}
		printf("exit\n");
		exit(g_minishell.exit_code);
	}

	else
		printf("exit\n");
	exit(g_minishell.exit_code);
	return (1);
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
		return (ft_env((tl(tmp->content))->envl, tmp));
	if (ft_strcmp((tl(tmp->content))->cmd, "export") == 0)
		return (ft_export(tmp, &flg));
	if (ft_strcmp((tl(tmp->content))->cmd, "exit") == 0)
		return (ft_exit_builtin(tmp));

	return (0);
}
