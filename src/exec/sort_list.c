/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:49 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/18 23:16:44 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*sort_list(t_expand* pp)
{
	char *swap;
	char *swap2;

	if(pp->key == NULL && pp->value == NULL)	
		return pp;
	t_expand *tmp;
	tmp = pp;
	while(pp->next)
	{
		if(pp->key[0] > pp->next->key[0])
		{
			swap = pp->key;
			swap2 = pp->value;
			pp->key = pp->next->key;
			pp->value = pp->next->value;
			pp->next->key = swap;
			pp->next->value = swap2;
			pp =tmp;
		}
		else 
		pp = pp->next;
	}
	pp = tmp;
	return(pp);
}
