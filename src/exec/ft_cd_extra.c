/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:18:27 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/20 20:14:27 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_old(char *pwd, char *old_pwd, t_list *tmp)
{
	while (((t_cmd *)(tmp->content))->envl)
	{
		if (!ft_strcmp(((t_cmd *)(tmp->content))->envl->key, "PWD"))
		{
			free(((t_cmd *)(tmp->content))->envl->value);
			((t_cmd *)(tmp->content))->envl->value = ft_strdup(pwd);
		}
		if (!ft_strcmp(((t_cmd *)(tmp->content))->envl->key, "OLDPWD"))
		{
			free(((t_cmd *)(tmp->content))->envl->value);
			if (old_pwd)
				((t_cmd *)(tmp->content))->envl->value = ft_strjoin("",
						old_pwd);
		}
		((t_cmd *)(tmp->content))->envl = ((t_cmd *)(tmp->content))->envl->next;
	}
}

int	valid_home(t_list *tmp)
{
	int	home;

	home = 0;
	while (((t_cmd *)(tmp->content))->envl)
	{
		if (ft_strcmp(((t_cmd *)(tmp->content))->envl->key, "HOME") == 0)
		{
			home++;
			if (chdir(((t_cmd *)(tmp->content))->envl->value))
				perror("minishell : ");
		}
		((t_cmd *)(tmp->content))->envl = ((t_cmd *)(tmp->content))->envl->next;
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
