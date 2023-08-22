/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:18:27 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/22 20:59:40 by rel-isma         ###   ########.fr       */
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
			if (old_pwd)
			{
				free(((t_cmd *)(tmp->content))->envl->value);
				((t_cmd *)(tmp->content))->envl->value = ft_strjoin("",
						old_pwd);
			}
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

int	cd_error(t_list *tmp)
{
	if (access(((t_cmd *)(tmp->content))->argms[1], F_OK) == -1)
	{
		if (((t_cmd *)(tmp->content))->pwd1)
			free(((t_cmd *)(tmp->content))->pwd1);
		ft_putstr_fd("minishell: cd: ", 2);
		perror(((t_cmd *)(tmp->content))->argms[1]);
		return (1);
	}
	if (access(((t_cmd *)(tmp->content))->argms[1], R_OK) == -1
		|| access(((t_cmd *)(tmp->content))->argms[1], X_OK) == -1)
	{
		if (((t_cmd *)(tmp->content))->pwd)
			free(((t_cmd *)(tmp->content))->pwd);
		ft_putstr_fd("minishell: cd: ", 2);
		perror(((t_cmd *)(tmp->content))->argms[1]);
	}
	return (0);
}
