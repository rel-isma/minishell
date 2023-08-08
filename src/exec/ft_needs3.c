/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:30 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/08 05:44:15 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	ft_echo(t_list *tmp) // echo the exit status
{
	t_list *tm;
	tm = tmp;
	int i = 1;
	int j = 2;

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
		{
			while ((tl(tmp->content))->argms[j])
			{
				write((tl(tmp->content))->oufile, (tl(tmp->content))->argms[j], ft_strlen((tl(tmp->content))->argms[j]));
				if ((tl(tmp->content))->argms[j + 1])
					write((tl(tmp->content))->oufile, " ", 1);
				j++;
			}
		}
		else
		{
			j = 1;
			while ((tl(tmp->content))->argms[j])
			{
				if ((tl(tmp->content))->argms[j + 1])
				{
					printf("%s", (tl(tmp->content))->argms[j]);
					printf(" ");
				}
				else
					printf("%s\n", (tl(tmp->content))->argms[j]);

				j++;
			}
		}
	}
	else
	{
		j = 1;
		while ((tl(tmp->content))->argms[j])
		{
			if ((tl(tmp->content))->argms[j + 1])
			{
				printf("%s", (tl(tmp->content))->argms[j]);
				printf(" ");
			}
			else
				printf("%s\n", (tl(tmp->content))->argms[j]);

			j++;
		}
	}
	return (0);
}
