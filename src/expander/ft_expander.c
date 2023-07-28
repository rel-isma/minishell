/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:43:50 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/28 01:26:19 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand	*ft_init_expander(char **env)
{
	t_expand	*expd;
	t_exp		exp;
	int			i;

	expd = NULL;
	i = 0;
	// if env empty add
	while (env[i])
	{
		exp.len1 = ft_strlen_env_aftr(env[i]);
		exp.key = ft_substr(env[i], 0, exp.len1);
		exp.len2 = ft_strlen_env_befor(env[i]);
		exp.vl = ft_substr(env[i], exp.len1 + 1, exp.len2);
		ft_lexeradd_back_expnd(&expd, ft_lexernew_expnd(exp.key, exp.vl));
		free(exp.key);
		free(exp.vl);
		i++;
	}
	return (expd);
}

void	ft_expander_env(t_lexer *lst, t_expand *expnd, int flg)
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
		ft_expand_valid(cur, tmp, flg);
		ft_expand_no_valid(tmp, str);
		if (tmp)
			tmp = tmp->next;
	}
}

void	ft_expander(t_lexer *lst, t_expand *exp, int flg)
{
	// t_expand	*exp;

	// exp = ft_init_expander(env);
	ft_expander_env(lst, exp, flg);
	// ft_free_list_exp(exp);
}
