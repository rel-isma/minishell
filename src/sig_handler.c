/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 01:39:19 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/20 01:39:44 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_minishell.heredoc_executing)
		{
			g_minishell.stdin_backup = dup(STDIN_FILENO);
			close(STDIN_FILENO);
			g_minishell.stop_exection = 1;
			return ;
		}
		if (!g_minishell.command_executing)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (signum == SIGQUIT)
		return ;
}

