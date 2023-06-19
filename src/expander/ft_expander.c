/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:43:50 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/18 23:36:55 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand 	*ft_lexernew_expnd(char *key_v, char *val)
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
	int len;

	len = 0;
	while (env[len] != '=')
	{
		len++;
	}
	return len;
}

int	ft_strlen_env_befor(char *env)
{
	int len;
	int	j;

	len = 0;
	j = 0;
	while (env[j])
	{
		if (env[j] == '=')
		{
			while (env[j])
			{
				len++;
				j++;
			}
		}
		j++;
	}
	return len;
}

void    ft_init_expander(char **env)
{
    t_expand *expd;
    // t_expand *tmp;
	char	*key;
	char	*vl;
    int     i;
    int len1;
    int len2;

	expd = NULL;
    i = 0;
	/////////////////////////////////////////////////////////
	// if env empty add 
	/////////////////////////////////////////////////////////
    while (env[i])
    {
		len1 = ft_strlen_env_aftr(env[i]);
		key = ft_substr(env[i], 0, len1);
		len2 = ft_strlen_env_befor(env[i]);
		vl = ft_substr(env[i], len1 + 1, len2);
		ft_lexeradd_back_expnd(&expd, ft_lexernew_expnd(key, vl));
		free(key);
		free(vl);
        i++;
    }
	// tmp = expd;
	// while (tmp)
	// {
	// 	printf("key = [%s]   vl = [%s]\n", tmp->key, tmp->value);
	// 	tmp = tmp->next;
	// }
}

int ft_expander(t_lexer *lst, char **env)
{
	(void)lst;
	ft_init_expander(env);
	return 0;
}