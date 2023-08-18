/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:51:42 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/18 23:21:41 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env_help(int *flg1, t_list *tmp, int i)
{
	int flg = 0;
	t_exp exp_e;

	exp_e.len1 = ft_strlen_env_aftr((tl(tmp->content))->argms[i],
		&flg);
	exp_e.key = ft_substr((tl(tmp->content))->argms[i], 0,
		exp_e.len1);
	exp_e.len2 = ft_strlen_env_befor((tl(tmp->content))->argms[i]);
	if (exp_e.len2 == 1 && (tl(tmp->content))->argms[i][exp_e.len1 + 1] == '\0')
	{
		*flg1 = 1;
		exp_e.vl = ft_strdup("");
	}
	else
	{
		if (flg)
			exp_e.len1 += 1;
		exp_e.vl = ft_substr((tl(tmp->content))->argms[i],
			exp_e.len1 + 1, exp_e.len2);
	}
	if (!ft_check_duble(exp_e.key, exp_e.vl, (tl(tmp->content))->envl, flg))
		ft_lexeradd_back_expnd(&(tl(tmp->content))->envl,
			ft_lexernew_expnd(exp_e.key, exp_e.vl));
	free(exp_e.key);
	free(exp_e.vl);
}

int ft_add_env(t_list *tmp, int *flg1)
{
	int i;

	i = 1;
	while ((tl(tmp->content))->argms[i])
	{
		if (syntax_export((tl(tmp->content))->argms[i]))
			return (1);
		else
		{
			add_env_help(flg1, tmp, i);
		}
		i++;
	}
	return 0;
}
int	ft_export(t_list *tmp, int *flg1) // not finsh
{
	int i;
	t_expand *p;
	

	i = 1;
	p = (tl(tmp->content))->envl;
	ft_print_export(tmp, *flg1, p);
	if ((tl(tmp->content))->argms[i])
	{
		if (ft_add_env(tmp, flg1))
			return 1;
	}
	return (0);
}

