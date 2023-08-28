/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:13:45 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/28 05:25:52 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (((str[0] != '+' && str[0] != '-') && !ft_isdigit(str[i]))
			|| (str[1] == '+' || str[1] == '-'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_long(const char *str)
{
	int					i;
	unsigned long long	r;
	int					s;

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
	if (ft_atoi_long(((t_cmd *)(tmp->content))->argms[1])
		|| ft_strlen((((t_cmd *)(tmp->content))->argms[1])) > 19
		|| syntax_exit(((t_cmd *)(tmp->content))->argms[1])
		|| ft_strlen(((t_cmd *)(tmp->content))->argms[1]) == 0)
	{
		write(2, "exit\n", 5);
		ft_putstr_fd("minishell : exit: ", 2);
		ft_putstr_fd(((t_cmd *)(tmp->content))->argms[1], 2);
		ft_putstr_fd("numeric argument required\n", 2);
		exit(255);
	}
	if (((t_cmd *)(tmp->content))->argms[2])
	{
		write(2, "exit\n", 5);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	ft_exit_builtin(t_list *tmp)
{
	int	status;

	if (((t_cmd *)(tmp->content))->argms[1])
	{
		if (failed_exit(tmp))
			return (1);
		else
		{
			status = ft_atoi(((t_cmd *)(tmp->content))->argms[1]);
			g_minishell.exit_code = status;
			write(2, "exit\n", 5);
			exit(g_minishell.exit_code);
		}
	}
	else
		write(2, "exit\n", 5);
	exit(g_minishell.exit_code);
	return (1);
}
