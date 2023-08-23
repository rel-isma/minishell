/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needs_cmds1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 04:14:54 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/23 18:12:37 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exeve_in_minishell(t_list *cmd, char **env)
{
	struct stat	file_info;

	execve(((t_cmd *)(cmd->content))->path,
		((t_cmd *)(cmd->content))->argms, env);
	if (stat(((t_cmd *)(cmd->content))->path, &file_info) == 0)
	{
		ft_putstr_fd("minishell ", 2);
		ft_putstr_fd(((t_cmd *)(cmd->content))->path, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	else
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, ((t_cmd *)(cmd->content))->path,
			ft_strlen(((t_cmd *)(cmd->content))->path));
		g_minishell.exit_code = 1;
		perror(" ");
		exit(127);
	}
}

void	ft_exec_in_child(t_list *cmd, char **env, int *fd, int old_fd)
{
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	if (((t_cmd *)(cmd->content))->oufilename)
		dup2(((t_cmd *)(cmd->content))->oufile, STDOUT_FILENO);
	if (old_fd != -1)
	{
		dup2(old_fd, STDIN_FILENO);
		close(old_fd);
	}
	if (((t_cmd *)(cmd->content))->infilename)
	{
		if ((ft_strncmp("/tmp/.heredoc>",
					((t_cmd *)(cmd->content))->infilename, 14) == 0))
			((t_cmd *)(cmd->content))->infile
				= open(((t_cmd *)(cmd->content))->infilename, O_RDONLY);
		dup2(((t_cmd *)(cmd->content))->infile, STDIN_FILENO);
	}
	if (ft_check_builting(cmd))
		return (g_minishell.exit_code = ft_builting(cmd),
			exit(g_minishell.exit_code));
	ft_exeve_in_minishell(cmd, env);
}

void	ft_free_tab(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	command_not_found(char *str)
{
	printf("minishell: %s: command not found\n", str);
	g_minishell.exit_code = 127;
}
