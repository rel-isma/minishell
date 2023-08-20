/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needs_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 01:32:31 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/20 01:47:42 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_shlvl(t_expand *envl)
{
	int lvl;

    lvl = 0;
	while(envl)
	{
		if(ft_strcmp(envl->key, "SHLVL") == 0)
		{
			if(ft_atoi(envl->value) < 0)
				envl->value = ft_strdup(ft_itoa(0));
			else if(ft_atoi(envl->value) == 999)
				envl->value = ft_strdup("");
			else if(envl->value == NULL)
				envl->value = ft_strdup(ft_itoa(1));
			else 
				envl->value = ft_strdup(ft_itoa(ft_atoi(envl->value) + 1));
			lvl++;
		}
		envl = envl->next;
	}
	if(!lvl)
		ft_lexeradd_back_expnd(&envl, ft_lexernew_expnd("SHLVL", "1"));
}

int	ft_check_argms(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		printf("Error : just like this please \n\t 👉👉 ./minishell 👈👈\n");
		return (1);
	}
	else
		return (0);
}

void	fu(void)
{
	system("leaks minishell");
}

void	ft_free_all_minishell(t_list *cmds)
{
	int		i;
	t_list	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		i = 0;
		while (((t_cmd *)(cmds->content))->argms[i])
		{
			free(((t_cmd *)(cmds->content))->argms[i]);
			((t_cmd *)(cmds->content))->argms[i] = NULL;
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
