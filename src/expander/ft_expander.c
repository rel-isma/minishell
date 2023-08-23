/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:43:50 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/23 08:57:57 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_empty(char **env, t_expand **expd)
{
	t_exp	exp;
	char	ptr[PATH_MAX];

	if (!env[0])
	{
		exp.key = ft_strdup("PWD");
		exp.vl = getcwd(ptr, sizeof(ptr));
		ft_l_back_expnd(expd, ft_lexernew_expnd(exp.key, exp.vl));
		free(exp.key);
		exp.key = ft_strdup("SHLVL");
		exp.vl = ft_strdup("1");
		ft_l_back_expnd(expd, ft_lexernew_expnd(exp.key, exp.vl));
		free(exp.key);
		free(exp.vl);
		exp.key = ft_strdup("_");
		exp.vl = ft_strdup("/usr/bin/env");
		ft_l_back_expnd(expd, ft_lexernew_expnd(exp.key, exp.vl));
		free(exp.key);
		free(exp.vl);
	}
}

t_expand	*ft_init_expander(char **env)
{
	t_expand	*expd;
	t_exp		exp;
	int			i;

	expd = NULL;
	i = 0;
	ft_add_empty(env, &expd);
	while (env[i])
	{
		exp.len1 = ft_strlen_env_aftr(env[i], 0);
		exp.key = ft_substr(env[i], 0, exp.len1);
		exp.len2 = ft_strlen_env_befor(env[i]);
		exp.vl = ft_substr(env[i], exp.len1 + 1, exp.len2);
		ft_l_back_expnd(&expd, ft_lexernew_expnd(exp.key, exp.vl));
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

	cur = NULL;
	tmp = lst;
	while (tmp)
	{
		cur = expnd;
		str = ft_strdup(tmp->value);
		ft_check_after_here_doc(&tmp);
		ft_expand_valid(cur, tmp, flg);
		ft_expand_no_valid(tmp, str);
		free(str);
		if (tmp)
			tmp = tmp->next;
	}
}

void	ft_expander(t_lexer *lst, t_expand *exp, int flg)
{
	ft_expander_env(lst, exp, flg);
}
