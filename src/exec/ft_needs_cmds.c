/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:57:30 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/09 12:48:55 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *path, t_expand *env, t_list *cmd)
{
	char	*str;

	(tl(cmd->content))->lvl = 1;
	while (env)
	{
		if (ft_strcmp(path, env->key) == 0)
		{
			str = env->value;
			(tl(cmd->content))->lvl = 0;
			return (str);
		}
		env = env->next;
	}
	return (NULL);
}

char	*ft_get_path(t_list *cmd)
{
	char	**paths;
	char	*path;
	char	*cmd_path;
	char	*cmd_path1;
	int		i;
	char	*cmd_str;

	cmd_str = (tl(cmd->content))->cmd;
	i = 0;
	if (cmd_str[0] == '/' || (ft_strnstr(cmd_str, "/", ft_strlen(cmd_str)))
		|| !ft_getenv("PATH", (tl(cmd->content))->envl, cmd)
		|| ft_check_builting(cmd))
		return (cmd_str);
	paths = ft_split(ft_getenv("PATH", (tl(cmd->content))->envl, cmd), ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		cmd_path1 = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(cmd_path1, (tl(cmd->content))->cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free(cmd_path1);
			path = cmd_path;
			ft_free_tab(paths);
			return (path);
		}
		i++;
		free(cmd_path);
		free(cmd_path1);
	}
	ft_free_tab(paths);
	return (NULL);
}

char	**ft_get_env_tab(t_list *cmd)
{
	int			len;
	int			i;
	t_expand	*cur_size;
	char		**env;
	char		*str;

	len = 0;
	i = 0;
	;
	cur_size = (tl(cmd->content))->envl;
	while (cur_size)
	{
		len++;
		cur_size = cur_size->next;
	}
	env = malloc((len + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	cur_size = (tl(cmd->content))->envl;
	while (cur_size)
	{
		str = ft_strjoin(cur_size->key, "=");
		env[i] = ft_strjoin(str, cur_size->value);
		cur_size = cur_size->next;
		i++;
		free(str);
	}
	env[i] = NULL;
	return (env);
}
