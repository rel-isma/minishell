/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:25 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/21 00:11:41 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void 	change_env_helper(t_list *tmp, int *i, int *j)
{
	char *tmp1;
		if (*i)
		{
			pwd_old(g_minishell.str, ((t_cmd *)(tmp->content))->pwd, tmp);
			free(((t_cmd *)(tmp->content))->pwd);
		}
		else
		{
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
			}	
		}
}
void	change_env(t_list *tmp, int *i, int *j)
{
	char	current_dir[PATH_MAX];

	if (getcwd(current_dir, sizeof(current_dir)))
		g_minishell.str = ft_strdup(getcwd(current_dir, sizeof(current_dir)));
	if (g_minishell.str)
	{
		change_env_helper(tmp, i, j);
	}
	else
		pwd_old(getcwd(current_dir, sizeof(current_dir)), getcwd(current_dir,
				sizeof(current_dir)), tmp);
}
int 	special_cases(t_list *tmp)
{
	if (ft_strcmp(((t_cmd *)(tmp->content))->argms[1], "~") == 0
		|| !((t_cmd *)(tmp->content))->argms[1])
		{
		cd_home(tmp);
		return(1);
		}
	else if (cd_root(((t_cmd *)(tmp->content))->argms[1]))
	{
		chdir("/");
		return(1);
	}
	return(0);
}
int	cd(t_list *tmp, int *i)
{
	char	current_dir[PATH_MAX];
	char	*str;

	if(special_cases(tmp))
		return(0);
	else
	{
		if (chdir(((t_cmd *)(tmp->content))->argms[1]))
			if (cd_error(tmp))
				return (1);
		if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		{
			*i = 1;
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			((t_cmd *)(tmp->content))->pwd = ft_strdup(g_minishell.str);
			str = ft_strdup(g_minishell.str);
			free(g_minishell.str);
			g_minishell.str = ft_strjoin(str, "/..");
			chdir(g_minishell.str);
			free(str);
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
