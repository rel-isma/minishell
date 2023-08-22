/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:51:42 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/22 07:31:42 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env_help(int *flg1, t_list *tmp, int i)
{
	int		flg;
	t_exp	exp_e;

	flg = 0;
	exp_e.len1 = ft_strlen_env_aftr(((t_cmd *)(tmp->content))->argms[i], &flg);
	exp_e.key = ft_substr(((t_cmd *)(tmp->content))->argms[i], 0, exp_e.len1);
	exp_e.len2 = ft_strlen_env_befor(((t_cmd *)(tmp->content))->argms[i]);
	if (exp_e.len2 == 1 && ((t_cmd *)(tmp->content))->argms[i][exp_e.len1
		+ 1] == '\0')
	{
		*flg1 = 1;
		exp_e.vl = ft_strdup("");
	}
	else
	{
		if (flg)
			exp_e.len1 += 1;
		exp_e.vl = ft_substr(((t_cmd *)(tmp->content))->argms[i], exp_e.len1
				+ 1, exp_e.len2);
	}
	if (!ft_check_duble(exp_e.key, exp_e.vl, ((t_cmd *)(tmp->content))->envl,
		flg))
		ft_lexeradd_back_expnd(&((t_cmd *)(tmp->content))->envl,
			ft_lexernew_expnd(exp_e.key, exp_e.vl));
	return (free(exp_e.key), free(exp_e.vl));
}

int	ft_add_env(t_list *tmp, int *flg1)
{
	int	i;

	i = 1;
	while (((t_cmd *)(tmp->content))->argms[i])
	{
		if (syntax_export(((t_cmd *)(tmp->content))->argms[i]))
			return (1);
		else
			add_env_help(flg1, tmp, i);
		i++;
	}
	return (0);
}

int	ft_export(t_list *tmp, int *flg1)
{
	int			i;
	t_expand	*p;

	i = 1;
	p = ((t_cmd *)(tmp->content))->envl;
	ft_print_export(tmp, *flg1, p);
	if (((t_cmd *)(tmp->content))->argms[i] && ft_strcmp(((t_cmd *)(tmp->content))->argms[i], "") != 0 )
	{
		if (ft_add_env(tmp, flg1))
			return (1);
	}
	return (0);
}
