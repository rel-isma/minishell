/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:18:27 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/18 18:19:03 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_old(char *pwd, char *old_pwd, t_list *tmp)
{
	while ((tl(tmp->content))->envl)
	{
		if (!ft_strcmp((tl(tmp->content))->envl->key, "PWD"))
		{
			free((tl(tmp->content))->envl->value);
			(tl(tmp->content))->envl->value = ft_strdup(pwd);
		}
		if (!ft_strcmp((tl(tmp->content))->envl->key, "OLDPWD"))
		{
			free((tl(tmp->content))->envl->value);
			if (old_pwd)
				(tl(tmp->content))->envl->value = ft_strjoin("", old_pwd);
		}
		(tl(tmp->content))->envl = (tl(tmp->content))->envl->next;
	}
}

int	valid_home(t_list *tmp)
{
	int	home;

	home = 0;
	while ((tl(tmp->content))->envl)
	{
		if (ft_strcmp((tl(tmp->content))->envl->key, "HOME") == 0)
		{
			home++;
			if (chdir((tl(tmp->content))->envl->value))
				return (1);
		}
		(tl(tmp->content))->envl = (tl(tmp->content))->envl->next;
	}
	return (home);
}

void	cd_home(t_list *tmp)
{
	if (valid_home(tmp) == 0)
		printf("HOME not set\n");
}

int	cd_root(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '/')
			return (0);
		i++;
	}
	return (1);
}
