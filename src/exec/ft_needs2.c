/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:28 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/04 11:53:05 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	ft_env(t_expand *pp, int *flg)
{
	while ((pp))
	{
		if (ft_strcmp(pp->value, "") == 0 && *flg)
		{
			printf("%s=\n", pp->key);
			pp = pp->next;
		}
		else
		{
			if (pp->key && !(ft_strcmp(pp->value, "") == 0))
				printf("%s", pp->key);
			if (ft_strcmp(pp->value, "") != 0)
				printf("=\"%s\"\n", pp->value);
			pp = pp->next;
		}
	}
	return (0);
}

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
int	ft_unset(t_list *tmp) // finish
{
	t_expand *cur;
	t_expand *next;
	t_expand *prev;
	int i = 1;

	next = NULL;
	prev = NULL;

	while ((tl(tmp->content))->argms[i])
	{
		cur = (tl(tmp->content))->envl;
		if (syntax_unset((tl(tmp->content))->argms[i]))
			return (1);
		else
		{
			while (cur)
			{
				if (ft_strcmp(cur->key, (tl(tmp->content))->argms[i]) == 0)
				{
					next = cur->next;
					if (prev)
						prev->next = next;
					else
						(tl(tmp->content))->envl = next;
					free(cur->value);
					free(cur);
				}
				else
					prev = cur;
				if (cur)
					cur = cur->next;
			}
		}
		i++;
	}
	return (0);
}

int	ft_pwd()
{
	char	ptr[PATH_MAX];

	if (getcwd(ptr, sizeof(ptr)))
	{
		printf("%s\n", ptr);
		return (0);
	}
	else 
		printf("%s\n", g_minishell.str);
	return (1);
}

