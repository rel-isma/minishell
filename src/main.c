/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:16:01 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/01 17:26:52 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		// if (g_minishell.heredoc_executing)
		// {
		// 	g_minishell.stdin_backup = dup(STDIN_FILENO);
		// 	close(STDIN_FILENO);
		// 	g_minishell.stop_exection = 1;
		// }
		if (!g_minishell.command_executing)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	if (signum == SIGQUIT)
		return ;
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

int	main(int ac, char *av[], char **env)
{
	char		*line;
	t_lexer		*cur;
	t_list		*commands;
	t_expand	*envl;

	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
    signal(SIGTSTP, SIG_IGN);
	if (ft_check_argms(ac, av))
		return (1);
	envl = ft_init_expander(env);
	while (1)
	{
		//reset_stdin
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			exit (0);
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
            ft_exec(commands, envl);
		}

		// int			i;
		// t_list		*tm = tmp;
		// while (tm)
		// {
		// 	i = 0;
		// 	printf("cmd->\t[%s]\t infile [%d]\t oufile [%d]\t infilename [%s]\t", ((t_cmd *)(tm->content))->cmd,
		// 		((t_cmd *)(tm->content))->infile, ((t_cmd *)(tm->content))->oufile, ((t_cmd *)(tm->content))->infilename);
		// 	while (((t_cmd *)(tm->content))->argms[i])
		// 	{
		// 		printf("arg->\t[%s]\t", ((t_cmd *)(tm->content))->argms[i]);
		// 		i++;
		// 	}
		// 	printf("\n");
		// 	tm = tm->next;
		// }
	}
	return (0);
}
