/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:25 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/28 17:54:09 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env_extra(t_list *tmp, int *j)
{
		char	*tmp1;
		if (!*j)
		{
			tmp1 = ft_strjoin(g_minishell.str, "/..");
			pwd_old(g_minishell.str, tmp1, tmp);
			free(tmp1);
		}
		else
		{
			pwd_old(g_minishell.str, ((t_cmd *)(tmp->content))->pwd1, tmp);
			free(((t_cmd *)(tmp->content))->pwd1);
			((t_cmd *)(tmp->content))->pwd1 = NULL;
		}
}
void	change_env_helper(t_list *tmp, int *i, int *j)
{


	if (*i)
	{
		pwd_old(g_minishell.str, ((t_cmd *)(tmp->content))->pwd, tmp);
		free(((t_cmd *)(tmp->content))->pwd);
		if (((t_cmd *)(tmp->content))->pwd1)
		{
			free(((t_cmd *)(tmp->content))->pwd1);
			((t_cmd *)(tmp->content))->pwd1 = NULL;
		}
	}
	else
		change_env_extra(tmp, j);
}

void	change_env(t_list *tmp, int *i, int *j)
{
	char	current_dir[PATH_MAX];

	if (getcwd(current_dir, sizeof(current_dir)))
	{
		if (g_minishell.str)
		{
			free(g_minishell.str);
			g_minishell.str = NULL;
		}
		g_minishell.str = ft_strdup(getcwd(current_dir, sizeof(current_dir)));
	}
	if (g_minishell.str)
		change_env_helper(tmp, i, j);
	else
		pwd_old(getcwd(current_dir, sizeof(current_dir)), getcwd(current_dir,
				sizeof(current_dir)), tmp);
}

int	special_cases(t_list *tmp)
{
	if (ft_strcmp(((t_cmd *)(tmp->content))->argms[1], "~") == 0
		|| ft_strlen(((t_cmd *)(tmp->content))->argms[1]) == 0
		|| !((t_cmd *)(tmp->content))->argms[1])
	{
		cd_home(tmp);
		return (1);
	}
	else if (cd_root(((t_cmd *)(tmp->content))->argms[1]))
	{
		chdir("/");
		return (1);
	}
	return (0);
}

void	ft_cd_helper(t_list *tmp, int *i)
{
	char *str;
	*i = 1;
			perror("minishell cd: ");
			((t_cmd *)(tmp->content))->pwd = ft_strdup(g_minishell.str);
			str = ft_strdup(g_minishell.str);
			free(g_minishell.str);
			g_minishell.str = NULL;
			if (access(((t_cmd *)(tmp->content))->argms[1], R_OK) == -1
				|| access(((t_cmd *)(tmp->content))->argms[1], X_OK) == -1)
				chdir(str);
			else
			{
				g_minishell.str = ft_strjoin(str, "/..");
				chdir(g_minishell.str);
			}
			free(str);
}
int	cd(t_list *tmp, int *i)
{
	char	current_dir[PATH_MAX];

	if (special_cases(tmp))
		return (0);
	else
	{
		if (chdir(((t_cmd *)(tmp->content))->argms[1]))
			if (cd_error(tmp))
				return (1);
		if (getcwd(current_dir, sizeof(current_dir)) == NULL)
			ft_cd_helper(tmp, i);
	}
	return (0);
}

int	ft_cd(t_list *tmp)
{
	char current_dir[PATH_MAX];
	int i;
	int j;

	i = 0;
	j = 0;
	if (getcwd(current_dir, sizeof(current_dir)))
	{
		j = 1;
		((t_cmd *)(tmp->content))->pwd1 = ft_strjoin("", getcwd(current_dir,
				sizeof(current_dir)));
	}
	if (cd(tmp, &i))
	{
		if (((t_cmd *)(tmp->content))->pwd1)
		{
			free(((t_cmd *)(tmp->content))->pwd1);
			((t_cmd *)(tmp->content))->pwd1 = NULL;
		}
		return (1);
	}
	change_env(tmp, &i, &j);
	return (0);
}
