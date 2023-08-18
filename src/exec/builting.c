/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:37 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/10 04:46:46 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 	syntax_exit(char *str)
{
	int i = 0;
	while(str[i])
	{
		if((str[0] != '+' && str[0] != '-')&& !ft_isdigit(str[i]))
			return(1);
		i++;
	}
	return(0);
}

int	ft_exit_builtin(t_list *tmp) // finish fot exit builting
{	
	int status;
	if((tl(tmp->content))->argms[1])
	{
		if((tl(tmp->content))->argms[2])
		{
		write(1, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 36);
		exit(1);
		}
		if(strlen((tl(tmp->content))->argms[1]) > 19  || syntax_exit((tl(tmp->content))->argms[1]))
		{
			printf("exit\n");
			printf("minishell : exit: %s : numeric argument required\n", (tl(tmp->content))->argms[1]);
			g_minishell.exit_code = 255;
			exit(g_minishell.exit_code);
		}
		else 
		{
		status = ft_atoi((tl(tmp->content))->argms[1]);
		if(status > 255)
		{
			status %= 256;
			g_minishell.exit_code = status;	
		}
		else if( status < 0)
			g_minishell.exit_code = 156;	
		else
			g_minishell.exit_code = status;	
		}
		printf("exit\n");
		exit(g_minishell.exit_code);
	}

	else
		printf("exit\n");
		exit(g_minishell.exit_code);
	return(1);
}


int	ft_builting(t_list *tmp) // not yet
{
	static int flg = 0;

	if (ft_strcmp((tl(tmp->content))->cmd, "echo") == 0)
		return (g_minishell.exit_code = ft_echo(tmp), 1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "pwd") == 0)
		return (g_minishell.exit_code = ft_pwd(), 1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "cd") == 0)
		return (g_minishell.exit_code = ft_cd(tmp), 1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "unset") == 0)
		return (g_minishell.exit_code = ft_unset(tmp), 1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "env") == 0)
		return (g_minishell.exit_code = ft_env((tl(tmp->content))->envl, tmp), 1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "export") == 0)
		return (g_minishell.exit_code = ft_export(tmp, &flg), 1);
	else if (ft_strcmp((tl(tmp->content))->cmd, "exit") == 0)
		return (g_minishell.exit_code = ft_exit_builtin(tmp), 1);
	return 0;
}
