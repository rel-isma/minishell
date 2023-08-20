/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:18:27 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/20 01:26:27 by rel-isma         ###   ########.fr       */
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
				return (-1);
		}
		((t_cmd *)(tmp->content))->envl = ((t_cmd *)(tmp->content))->envl->next;
	}
	return (home);
}

void	cd_home(t_list *tmp)
{
	if (valid_home(tmp) == 0)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	else if (valid_home(tmp) == -1)
	{
		ft_putstr_fd("minishell: cd: " , 2);
		ft_putstr_fd(((t_cmd *)(tmp->content))->envl->value, 2);
		perror(" ");
	}	
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
