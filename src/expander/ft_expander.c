/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:43:50 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/21 11:11:08 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand	*ft_init_expander(char **env)
{
	t_expand	*expd;
	char		*key;
	char		*vl;
	int			i;
	int			len1;
	int			len2;

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
	return (expd);
}

void	ft_expander_env(t_lexer *lst, t_expand *expnd)
{
	t_lexer		*tmp;
	t_expand	*cur;
	char		*str;

	tmp = lst;
	while (tmp)
	{
		cur = expnd;
		str = ft_strdup(tmp->value);
		ft_check_after_here_doc(&tmp);
		ft_expand_valid(cur, tmp);
		ft_expand_no_valid(tmp, str);
		if (tmp)
			tmp = tmp->next;
	}
}

t_expand	*ft_expander(t_lexer *lst, char **env)
{
	t_expand	*exp;

	exp = ft_init_expander(env);
	ft_expander_env(lst, exp);
	return (exp);
}
