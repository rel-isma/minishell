/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:30 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/19 02:39:05 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	no_new_line(t_list *tmp)
{
	int	j;

	j = 2;
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
		printf("\n");
		return (1);
	}
	if (((t_cmd *)(tmp->content))->argms[1][0] == '-'
		&& ((t_cmd *)(tmp->content))->argms[1][1] == 'n')
	{
		while (((t_cmd *)(tmp->content))->argms[1][i] == 'n')
			i++;
		if (((t_cmd *)(tmp->content))->argms[1][i] == '\0')
			no_new_line(tm);
		else
			new_line(tm);
	}
	else
		new_line(tm);
	return (0);
}
