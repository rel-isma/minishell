/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:57:30 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/19 03:06:37 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *path, t_expand *env, t_list *cmd)
{
	char	*str;

	((t_cmd *)(cmd->content))->lvl = 1;
	while (env)
	{
		if (ft_strcmp(path, env->key) == 0)
		{
			str = env->value;
			((t_cmd *)(cmd->content))->lvl = 0;
			return (str);
		}
		env = env->next;
	}
	return (NULL);
}

char	*ft_get_path(t_list *cmd)
{
	char	**paths;
	char	*cmd_path[2];
	int		i;

	i = 0;
	if (((t_cmd *)(cmd->content))->cmd[0] == '/'
		|| (ft_strnstr(((t_cmd *)(cmd->content))->cmd, "/",
		ft_strlen(((t_cmd *)(cmd->content))->cmd))) || !ft_getenv("PATH",
		((t_cmd *)(cmd->content))->envl, cmd) || ft_check_builting(cmd))
		return (ft_strdup(((t_cmd *)(cmd->content))->cmd));
	paths = ft_split(ft_getenv("PATH", ((t_cmd *)(cmd->content))->envl, cmd),
			':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		cmd_path[0] = ft_strjoin(paths[i], "/");
		cmd_path[1] = ft_strjoin(cmd_path[0], ((t_cmd *)(cmd->content))->cmd);
		if (access(cmd_path[1], F_OK | X_OK) == 0)
			return (free(cmd_path[0]), ft_free_tab(paths), cmd_path[1]);
		i++;
		free(cmd_path[1]);
		free(cmd_path[0]);
	}
	return (ft_free_tab(paths), NULL);
}

char	**ft_get_env_tab(t_list *cmd)
{
	int			len;
	t_expand	*cur_size;
	char		**env;
	char		*str;

	len = 0;
	cur_size = ((t_cmd *)(cmd->content))->envl;
	while (cur_size)
	{
		len++;
		cur_size = cur_size->next;
	}
	env = malloc((len + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	cur_size = ((t_cmd *)(cmd->content))->envl;
	len = 0;
	while (cur_size)
	{
		str = ft_strjoin(cur_size->key, "=");
		env[len++] = ft_strjoin(str, cur_size->value);
		cur_size = cur_size->next;
		free(str);
	}
	return (env[len] = NULL, env);
}
