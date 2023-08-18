/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:37:26 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/18 18:46:56 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_unset(char *str)
{
	int	j;

	j = 0;
	if (ft_isdigit(str[0]))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", str);
		return (1);
	}
	while (str[j])
	{
		if (!ft_isalnum(str[j]) && str[j] != '_' )
		{
			printf("minishell: unset: `%s': not a valid identifier\n", str);
			return (1);
		}
		j++;
	}
	return (0);
}

void	delete(t_expand *cur, t_list *tmp, int *i)
{
	while (cur)
	{
		if (ft_strcmp(cur->key, (tl(tmp->content))->argms[*i]) == 0)
		{
			free(cur->key);
			cur->key = NULL;
			free(cur->value);
			cur->value = NULL;
		}
		cur = cur->next;
	}
}

int	ft_unset(t_list *tmp)
{
	t_expand	*cur;
	t_expand	*next;
	t_expand	*prev;
	int			i;

	i = 1;
	next = NULL;
	prev = NULL;
	while ((tl(tmp->content))->argms[i])
	{
		cur = (tl(tmp->content))->envl;
		if (syntax_unset((tl(tmp->content))->argms[i]))
			return (1);
		else 
			delete(cur, tmp, &i);
		i++;
	}
	return (0);
}
