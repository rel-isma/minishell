/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:25 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/09 13:17:59 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	{
		printf("HOME not set\n");
	}
}
int 	cd_root(char *str)
{
	int i = 0;
	while(str[i])
	{	
		if(str[i] != '/')
			return(0);
		i++;
	}
	return(1);
}
int	ft_cd(t_list *tmp) // finish
{
	int cd = 0;
	char current_dir[PATH_MAX];
	char *old_pwd;
	char *cd_dir = malloc(sizeof(char) * PATH_MAX);
		g_minishell.err = 0;
	if ((tl(tmp->content))->argms[1] == NULL || ft_strcmp((tl(tmp->content))->argms[1], "~") == 0)
	{
		cd = 1;
		cd_home(tmp);
	}
	else if(cd_root((tl(tmp->content))->argms[1]))
		chdir("/");
	if(getcwd(current_dir, sizeof(current_dir)))
		old_pwd =  ft_strdup(getcwd(current_dir, sizeof(current_dir)));
	cd_dir = ft_strjoin(current_dir, "/");
	cd_dir = ft_strjoin(cd_dir, (tl(tmp->content))->argms[1]);
	if(chdir(cd_dir) == 0)
		g_minishell.err = 1;
	if (chdir(cd_dir) && !cd)
	{
		(tl(tmp->content))->pwd = getcwd(current_dir, sizeof(current_dir));
		if (getcwd(current_dir, sizeof(current_dir)))
		{
			printf("minishell : cd %s No such file or directory\n", (tl(tmp->content))->argms[1]);
			g_minishell.exit_code = 1;
		}
		if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		{
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			chdir("..");
		}
	}
	if(!cd)
	{
		while((tl(tmp->content))->envl)
		{
			if(g_minishell.err)
			{
			if (ft_strcmp((tl(tmp->content))->envl->key, "OLDPWD") == 0)
			{
				free((tl(tmp->content))->envl->value);
				(tl(tmp->content))->envl->value = ft_strdup(old_pwd);
			}
			if (ft_strcmp((tl(tmp->content))->envl->key, "PWD") == 0)
			{
				free((tl(tmp->content))->envl->value);
				g_minishell.err = 0;
				if(getcwd(current_dir, sizeof(current_dir)))
					(tl(tmp->content))->envl->value = ft_strdup(getcwd(current_dir, sizeof(current_dir)));
			}
			}
		(tl(tmp->content))->envl = (tl(tmp->content))->envl->next;
		}
		g_minishell.str = ft_strdup(cd_dir);
	}
	free(cd_dir);
	return (0);
}
////////////////
