/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 02:04:03 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/19 02:47:01 by rel-isma         ###   ########.fr       */
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
		if (!ft_isalnum(str[j]) && str[j] != '_')
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
		if (ft_strcmp(cur->key, ((t_cmd *)(tmp->content))->argms[*i]) == 0)
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
	while (((t_cmd *)(tmp->content))->argms[i])
	{
		cur = ((t_cmd *)(tmp->content))->envl;
		if (syntax_unset(((t_cmd *)(tmp->content))->argms[i]))
			return (1);
		else
			delete (cur, tmp, &i);
		i++;
	}
	return (0);
}
