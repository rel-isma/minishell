/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 02:04:03 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/23 00:27:20 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_unset(char *str)
{
	int	j;

	j = 0;
	if (ft_strlen(str) == 0)
	{
		printf("minishell: unset: `%s': not a valid identifier\n", str);
		return (1);
	}
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

void	delete(t_expand **envl, char *key)
{
	t_expand	*current;
	t_expand	*previous;
	t_expand	*to_free;

	current = *envl;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous == NULL)
				*envl = current->next;
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			to_free = current;
			current = current->next;
			free(to_free);
			break ;
		}
		previous = current;
		current = current->next;
	}
}

int	ft_unset(t_list *tmp, t_expand **envl)
{
	int	i;

	i = 1;
	while (((t_cmd *)(tmp->content))->argms[i])
	{
		if (syntax_unset(((t_cmd *)(tmp->content))->argms[i]))
			return (1);
		else
			delete (envl, ((t_cmd *)(tmp->content))->argms[i]);
		i++;
	}
	return (0);
}
