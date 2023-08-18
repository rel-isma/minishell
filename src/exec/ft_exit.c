/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:13:45 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/18 18:32:29 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[0] != '+' && str[0] != '-') && !ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_long(const char *str)
{
	int		i;
	size_t	r;
	int		s;

	i = 0;
	r = 0;
	s = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -s;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - 48;
		i++;
	}
	if (r > 9223372036854775807)
		return (1);
	return (0);
}

int	failed_exit(t_list *tmp)
{
	if ((tl(tmp->content))->argms[2])
	{
		write(1, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	if (ft_atoi_long((tl(tmp->content))->argms[1]) 
		|| syntax_exit((tl(tmp->content))->argms[1]))
	{
		printf("exit\n");
		printf("minishell : exit: %s : numeric argument required\n", 
			(tl(tmp->content))->argms[1]);
		g_minishell.exit_code = 255;
		exit(g_minishell.exit_code);
	}
	return (0);
}

int	ft_exit_builtin(t_list *tmp)
{
	int	status;

	if ((tl(tmp->content))->argms[1])
	{
		if (failed_exit(tmp))
			exit (1);
		status = ft_atoi((tl(tmp->content))->argms[1]);
		if (status > 255)
		{
			status %= 256;
			g_minishell.exit_code = status;
		}
		else if (status < 0)
			g_minishell.exit_code = 156;
		else
			g_minishell.exit_code = status;
		printf("exit\n");
		exit(g_minishell.exit_code);
	}
	else
		printf("exit\n");
	exit(g_minishell.exit_code);
	return (1);
}
