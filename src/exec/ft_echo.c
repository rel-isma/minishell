/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:30 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/18 18:26:34 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_line(t_list *tmp)
{
	int	j;

	j = 1;
	while ((tl(tmp->content))->argms[j])
	{
		if ((tl(tmp->content))->argms[j + 1])
		{
			write((tl(tmp->content))->oufile, (tl(tmp->content))->argms[j],
				ft_strlen((tl(tmp->content))->argms[j]));
			write((tl(tmp->content))->oufile, " ", 1);
		}
		else
		{
			write((tl(tmp->content))->oufile, (tl(tmp->content))->argms[j],
				ft_strlen((tl(tmp->content))->argms[j]));
			write((tl(tmp->content))->oufile, "\n", 1);
		}
		j++;
	}
}

void	no_new_line(t_list *tmp)
{
	int	j;

	j = 2;
	while ((tl(tmp->content))->argms[j])
	{
		write((tl(tmp->content))->oufile, (tl(tmp->content))->argms[j],
			ft_strlen((tl(tmp->content))->argms[j]));
		if ((tl(tmp->content))->argms[j + 1])
			write((tl(tmp->content))->oufile, " ", 1);
		j++;
	}
}

int	ft_echo(t_list *tmp)
{
	t_list	*tm;
	int		i;

	tm = tmp;
	i = 1;
	if (!(tl(tmp->content))->argms[1])
	{
		printf("\n");
		return (1);
	}
	if ((tl(tmp->content))->argms[1][0] == '-'
		&& (tl(tmp->content))->argms[1][1] == 'n')
	{
		while ((tl(tmp->content))->argms[1][i] == 'n')
			i++;
		if ((tl(tmp->content))->argms[1][i] == '\0')
			no_new_line(tm);
		else
			new_line(tm);
	}
	else
		new_line(tm);
	return (0);
}
