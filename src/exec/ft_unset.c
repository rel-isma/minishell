/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 02:04:03 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/21 22:58:09 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_unset(char *str)
{
	int	j;

	j = 0;
	if(ft_strlen(str) == 0)
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

	current = *envl;
	previous = NULL;
	if (syntax_unset(key))
			return ;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->key);
			current->key = NULL;
			free(current->value);
			current->value = NULL;
			current->flg = 0;
		}
		current = current->next;
	}
}

int	ft_unset(t_list *tmp)
{
	int	i;

	i = 1;
	while (((t_cmd *)(tmp->content))->argms[i])
	{
			delete (&((t_cmd *)(tmp->content))->envl,
				((t_cmd *)(tmp->content))->argms[i]);
		i++;
	}
	return (0);
}
