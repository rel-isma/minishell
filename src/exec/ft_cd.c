/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:25 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/19 02:43:27 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_error(t_list *tmp)
{
	if (access(((t_cmd *)(tmp->content))->argms[1], F_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		perror(((t_cmd *)(tmp->content))->argms[1]);
		return (1);
	}
	if (access(((t_cmd *)(tmp->content))->argms[1], R_OK) == -1
		|| access(((t_cmd *)(tmp->content))->argms[1], X_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		perror(((t_cmd *)(tmp->content))->argms[1]);
	}
	return (0);
}

void	change_env(t_list *tmp, int *i, int *j)
{
	char	current_dir[PATH_MAX];

	if (getcwd(current_dir, sizeof(current_dir)))
		g_minishell.str = ft_strdup(getcwd(current_dir, sizeof(current_dir)));
	if (g_minishell.str)
	{
		if (*i)
			pwd_old(g_minishell.str, ((t_cmd *)(tmp->content))->pwd, tmp);
		else
		{
			if (!*j)
				pwd_old(g_minishell.str, ft_strjoin(g_minishell.str, "/.."),
					tmp);
			else
				pwd_old(g_minishell.str, ((t_cmd *)(tmp->content))->pwd1, tmp);
		}
	}
	else
		pwd_old(getcwd(current_dir, sizeof(current_dir)), getcwd(current_dir,
				sizeof(current_dir)), tmp);
}

int	cd(t_list *tmp, int *i)
{
	char	current_dir[PATH_MAX];

	if (cd_root(((t_cmd *)(tmp->content))->argms[1]))
		chdir("/");
	else if (ft_strcmp(((t_cmd *)(tmp->content))->argms[1], "~") == 0
		|| !((t_cmd *)(tmp->content))->argms[1])
		cd_home(tmp);
	else
	{
		if (chdir(((t_cmd *)(tmp->content))->argms[1]))
			if (cd_error(tmp))
				return (1);
		if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		{
			*i = 1;
			((t_cmd *)(tmp->content))->pwd = ft_strdup(g_minishell.str);
			g_minishell.str = ft_strjoin(g_minishell.str, "/..");
			chdir(g_minishell.str);
		}
	}
	return (0);
}

int	ft_cd(t_list *tmp)
{
	char	current_dir[PATH_MAX];
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (getcwd(current_dir, sizeof(current_dir)))
	{
		j = 1;
		((t_cmd *)(tmp->content))->pwd1 = ft_strjoin("", getcwd(current_dir,
					sizeof(current_dir)));
	}
	if (cd(tmp, &i))
		return (1);
	change_env(tmp, &i, &j);
	return (0);
}
