/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needs_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 01:32:31 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/23 02:49:53 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_helper_shlvl(t_expand *envl)
{
	char	*it2;

	if (ft_atoi(envl->value) < 0)
	{
		free(envl->value);
		envl->value = ft_strdup("0");
	}
	else if (ft_atoi(envl->value) == 999)
	{
		free(envl->value);
		envl->value = ft_strdup("");
	}
	else if (envl->value == NULL || ft_atoi(envl->value) >= 1000)
	{
		free(envl->value);
		envl->value = ft_strdup("1");
	}
	else
	{
		it2 = ft_itoa(ft_atoi(envl->value) + 1);
		free(envl->value);
		envl->value = ft_strdup(it2);
		free(it2);
	}
}

void	ft_shlvl(t_expand *mini)
{
	int			lvl;
	t_expand	*envl;

	lvl = 0;
	envl = mini;
	while (envl)
	{
		if (ft_strcmp(envl->key, "SHLVL") == 0)
		{
			ft_helper_shlvl(envl);
			lvl++;
		}
		envl = envl->next;
	}
	if (!lvl)
		ft_l_back_expnd(&mini, ft_lexernew_expnd("SHLVL", "1"));
}

int	ft_check_argms(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		printf("Error : just like this please 😅😅😅\n\t 👉👉 ./minishell 👈👈\n");
		return (1);
	}
	else
		return (0);
}

void	ft_free_all_minishell(t_list *cmds)
{
	int		i;
	t_list	*tmp;

	while (cmds)
	{
		if (((t_cmd *)(cmds->content))->infilename
			&& (ft_strncmp("/tmp/.heredoc>",
					((t_cmd *)(cmds->content))->infilename, 14) == 0))
			free(((t_cmd *)(cmds->content))->infilename);
		tmp = cmds->next;
		i = 0;
		while (((t_cmd *)(cmds->content))->argms[i])
		{
			free(((t_cmd *)(cmds->content))->argms[i]);
			i++;
		}
		free(((t_cmd *)(cmds->content))->argms);
		free(((t_cmd *)(cmds->content))->cmd);
		free(((t_cmd *)(cmds->content)));
		free(cmds);
		cmds = tmp;
	}
}

void	close_all_fds(t_list *cmd)
{
	while (cmd)
	{
		if (((t_cmd *)(cmd->content))->infile != 0)
			close(((t_cmd *)(cmd->content))->infile);
		if (((t_cmd *)(cmd->content))->oufile != 1)
			close(((t_cmd *)(cmd->content))->oufile);
		cmd = cmd->next;
	}
}
