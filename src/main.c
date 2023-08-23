/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:16:01 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/23 18:02:47 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_helper(char *line, t_lexer *cur, t_list *commands, t_expand *envl)
{
	t_expand *curr;
	int i = 1;

	curr = envl;
	if (!line)
		{
			free_list(envl);
			write(2, "exit\n", 2);
			exit(g_minishell.exit_code);
		}
		add_history(line);
		cur = ft_lexer(line);
		if (ft_syntax_errors(cur))
		{
			ft_free_lexer(cur);
			return (1);
		}
		ft_expander(cur, envl, 1);
		commands = ft_join_argms(&cur, envl);
		if (commands)
		{
			free(g_minishell.cmd);
			while (((t_cmd *)(commands->content))->argms[i])
				i++;
			i--;
			g_minishell.cmd = ft_strdup(((t_cmd *)(commands->content))->argms[i]);
			(((t_cmd *)(commands->content))->pwd1) = NULL;
			(((t_cmd *)(commands->content))->pwd) = NULL;
			ft_exec(commands);
			envl = ((t_cmd *)(commands->content))->envl;
			while(curr)
			{
				if(ft_strcmp(curr->key, "_") == 0 && g_minishell.cmd)
				{
					free(curr->value);
					curr->value =ft_strdup(g_minishell.cmd);
				}
				curr = curr->next;
			}
			ft_free_all_minishell(commands);
		}
	return(0);
}
void	signals_minishell(void)
{
	if (g_minishell.stdin_backup != -1)
	{
		dup2(g_minishell.stdin_backup, STDIN_FILENO);
		close(g_minishell.stdin_backup);
		g_minishell.stdin_backup = -1;
		g_minishell.stop_exection = 0;
		g_minishell.heredoc_executing = 1;
	}
}

void	fu(void)
{
	system("leaks minishell");
}
int	main(int ac, char *av[], char **env)
{
	char		*line;
	t_lexer		*cur;
	t_list		*commands;
	t_expand	*envl;

	// atexit(fu);
	rl_catch_signals = 0;
	g_minishell.stdin_backup = -1;
	cur = NULL;
	commands = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, SIG_IGN);
	if (ft_check_argms(ac, av))
		return (1);
	envl = ft_init_expander(env);
	ft_shlvl(envl);
	while (1)
	{
		signals_minishell();
		g_minishell.stop_exection = 0;
		line = readline("minishell$ ");
		if(main_helper(line, cur, commands, envl))
			continue;
	}
	return (0);
}
