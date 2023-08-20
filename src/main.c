/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:16:01 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/20 02:34:36 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char **env)
{
	char		*line;
	t_lexer		*cur;
	t_list		*commands;
	t_expand	*envl;

	rl_catch_signals = 0;
	g_minishell.stdin_backup = -1;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, SIG_IGN);
	// if (ft_check_argms(ac, av))
	// 	return (1);
	envl = ft_init_expander(env);
	ft_shlvl(envl);
	if (ac == 3)
	{
		if (ft_strcmp(av[1], "-c") == 0)
		{
			line = ft_strdup(av[2]);
			if (!line)
			{
				printf("exit\n");
				exit(g_minishell.exit_code);
			}
			// if (input && input[0])
			// {
			// 	add_history(input);
			// 	//input = expand_input(env_s, input);
			// 	//printf("our input : %s\n", input);
			// 	g_input_line(input);
			// 	if(check_redirection(input))
			// 		main2(input, env_s);
			// }
			// free(input);
			add_history(line);
			cur = ft_lexer(line);
			if (ft_syntax_errors(cur))
			{
				ft_free_lexer(cur);
				return 0;
			}
			ft_expander(cur, envl, 1);
			commands = ft_join_argms(&cur, envl);
			if (commands)
			{
				ft_exec(commands);
				ft_free_all_minishell(commands);
			}
			}
			return (0);
	}
	while (1)
	{
		if (g_minishell.stdin_backup != -1)
		{
			dup2(g_minishell.stdin_backup, STDIN_FILENO);
			close(g_minishell.stdin_backup);
			g_minishell.stdin_backup = -1;
			g_minishell.stop_exection = 0;
			g_minishell.heredoc_executing = 1;
		}
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			exit(g_minishell.exit_code);
		}
		add_history(line);
		cur = ft_lexer(line);
		if (ft_syntax_errors(cur))
		{
			ft_free_lexer(cur);
			continue ;
		}
		ft_expander(cur, envl, 1);
		commands = ft_join_argms(&cur, envl);
		if (commands)
		{
			ft_exec(commands);
			ft_free_all_minishell(commands);
		}
	}
	return (0);
}
