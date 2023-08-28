/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:30 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/28 13:47:22 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_args(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (str[0] != '-' || !str[i])
		return (0);
	while (str[i])
	{
		if (str[0] != '-' || str[i] != 'n')
			return (0);
		else
			i++;
	}
	return (1);
}

void	new_line(t_list *tmp)
{
	int	j;

	j = 1;
	while (((t_cmd *)(tmp->content))->argms[j])
	{
		if (((t_cmd *)(tmp->content))->argms[j + 1])
		{
			write(((t_cmd *)(tmp->content))->oufile,
				((t_cmd *)(tmp->content))->argms[j],
				ft_strlen(((t_cmd *)(tmp->content))->argms[j]));
			write(((t_cmd *)(tmp->content))->oufile, " ", 1);
		}
		else
		{
			write(((t_cmd *)(tmp->content))->oufile,
				((t_cmd *)(tmp->content))->argms[j],
				ft_strlen(((t_cmd *)(tmp->content))->argms[j]));
			write(((t_cmd *)(tmp->content))->oufile, "\n", 1);
		}
		j++;
	}
}

void	no_new_line(t_list *tmp, int *i)
{
	int	j;

	j = *i;
	while (((t_cmd *)(tmp->content))->argms[j])
	{
		write(((t_cmd *)(tmp->content))->oufile,
			((t_cmd *)(tmp->content))->argms[j],
			ft_strlen(((t_cmd *)(tmp->content))->argms[j]));
		if (((t_cmd *)(tmp->content))->argms[j + 1])
			write(((t_cmd *)(tmp->content))->oufile, " ", 1);
		j++;
	}
}

int	ft_echo(t_list *tmp)
{
	t_list	*tm;
	int		i;

	tm = tmp;
	i = 1;
	if (!((t_cmd *)(tmp->content))->argms[1])
	{
		ft_putstr_fd("\n", ((t_cmd *)(tmp->content))->oufile);
		return (0);
	}
	else
	{
		while (check_args(((t_cmd *)(tmp->content))->argms[i]))
			i++;
		if (i > 1)
			no_new_line(tmp, &i);
		else
			new_line(tm);
	}
	return (0);
}
