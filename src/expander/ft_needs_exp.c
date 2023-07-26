/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:47:39 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/26 21:44:48 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand	*ft_lexernew_expnd(char *key_v, char *val)
{
	t_expand	*node;

	node = (t_expand *)malloc(sizeof(t_expand));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key_v);
	node->value = ft_strdup(val);
	node->next = NULL;
	return (node);
}

void	ft_lexeradd_back_expnd(t_expand **lst, t_expand *new)
{
	t_expand	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->next = NULL;
}

int	ft_strlen_env_aftr(char *env)
{
	int	len;

	len = 0;
	while (env[len] != '=')
		len++;
	return (len);
}

int	ft_strlen_env_befor(char *env)
{
	int	len;
	int	j;

	len = 0;
	j = 0;
	while (env[j])
	{
		if (env[j] == '=')
		{
			while (env[++j])
			{
				len++;
				// j++;
			}
		}
		if (env[j] == 0)
			break ;
		j++;
	}
	return (len);
}

void	ft_free_list_exp(t_expand *list)
{
	int			i;
	t_expand	*tmp;

	i = 0;
	while (list)
	{
		tmp = list->next;
		free(list->value);
		free(list->key);
		free(list);
		list = tmp;
	}
}
