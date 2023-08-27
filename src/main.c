/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:16:01 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/27 18:46:40 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_main_helper(t_lexer *cur, t_list *commands, t_expand **envl)
{
	char		*line;
	int			i;

	i = 0;
	line = readline("minishell$ ");
	if (!line)
	{
		free_list(*envl);
		printf("exit\n");
		exit(g_minishell.exit_code);
	}
	add_history(line);
	cur = ft_lexer(line);
	if (ft_syntax_errors(cur))
		return (ft_free_lexer(cur));
	ft_expander(cur, *envl, 1);
	commands = ft_join_argms(&cur, *envl);
	if (commands)
	{
		(((t_cmd *)(commands->content))->pwd1) = NULL;
		(((t_cmd *)(commands->content))->pwd) = NULL;
		ft_exec(commands);
		ft_free_all_minishell(commands);
	}
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

int	main(int ac, char *av[], char **env)
{
	t_lexer	*cur;
	t_list	*commands;

	rl_catch_signals = 0;
	g_minishell.stdin_backup = -1;
	cur = NULL;
	commands = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, SIG_IGN);
	if (ft_check_argms(ac, av))
		return (1);
	g_minishell.envl = ft_init_expander(env);
	ft_shlvl(g_minishell.envl);
	while (1)
	{
		signals_minishell();
		g_minishell.stop_exection = 0;
		ft_main_helper(cur, commands, &g_minishell.envl);
	}
	return (0);
}
