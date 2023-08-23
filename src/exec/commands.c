/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:39 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/23 16:36:56 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_helper_exe(t_list *cmd, int *fd, int old_fd, pid_t *pid)
{
	char	**env;

	if (ft_strcmp(((t_cmd *)(cmd->content))->cmd, "..") == 0
			|| ft_strcmp(((t_cmd *)(cmd->content))->cmd, ".") == 0)
		return (command_not_found(((t_cmd *)(cmd->content))->cmd), 0);
	((t_cmd *)(cmd->content))->path = ft_get_path(cmd);
	env = ft_get_env_tab(cmd);
	if (((t_cmd *)(cmd->content))->path == NULL)
	{
		command_not_found(((t_cmd *)(cmd->content))->cmd);
		free(((t_cmd *)(cmd->content))->path);
		ft_free_tab(env);
		return (0);
	}
	*pid = fork();
	if (*pid == -1)
		return (perror("fork"), free(((t_cmd *)(cmd->content))->path), ft_free_tab(env), -1);
	else if (*pid == 0)
		ft_exec_in_child(cmd, env, fd, old_fd);
	free(((t_cmd *)(cmd->content))->path);
	ft_free_tab(env);
	return (0);
}

int	ft_handel_cmd_not_found(t_list *cmd)
{
	if (((t_cmd *)(cmd->content))->cmd[0] == '\0'
		&& ((t_cmd *)(cmd->content))->type != 0
		&& ((t_cmd *)(cmd->content))->type != WHITE_SPACE
		&& g_minishell.env != 5)
	{
		command_not_found(((t_cmd *)(cmd->content))->cmd);
		return (0);
	}
	return (1);
}

void	ft_wait_last_command(pid_t pid)
{
	waitpid(pid, &g_minishell.exit_code, 0);
	if (WIFEXITED(g_minishell.exit_code))
		g_minishell.exit_code = WEXITSTATUS(g_minishell.exit_code);
}

int	ft_exec_cmd(t_list *cmd, int *fd, int old_fd)
{
	pid_t	pid;

	pid = 0;
	if (!ft_handel_cmd_not_found(cmd))
		return (0);
	if (((t_cmd *)(cmd->content))->argms[0]
		&& ((t_cmd *)(cmd->content))->argms[0][0] != '\0'
		&& ((t_cmd *)(cmd->content))->infile != -1)
		if (ft_helper_exe(cmd, fd, old_fd, &pid) == -1)
			return (-1);
	if (!cmd->next)
		ft_wait_last_command(pid);
	if (cmd->next)
		close(fd[1]);
	if (old_fd != -1)
		close(old_fd);
	return (0);
}

void	ft_commands(t_list *commands)
{
	t_list	*curr;
	int		old_fd;
	int		fd[2];

	if (g_minishell.stop_exection)
		return ;
	fd[0] = -1;
	fd[1] = -1;
	curr = commands;
	while (curr)
	{
		g_minishell.command_executing = 1;
		old_fd = fd[0];
		if (curr->next)
			pipe(fd);
		if (ft_exec_cmd(curr, fd, old_fd) == -1)
			break ;
		curr = curr->next;
	}
	while (wait(NULL) != -1)
		;
	close_all_fds(commands);
	g_minishell.command_executing = 0;
}
