/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:16:01 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/17 20:00:39 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_minishell.heredoc_executing)
		{
			g_minishell.stdin_backup = dup(STDIN_FILENO);
			close(STDIN_FILENO);
			g_minishell.stop_exection = 1;
		}
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

void	ft_free_all_minishell(t_list *cmds)
{
	int i;
	t_list	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		i = 0;
		while ((tl(cmds->content))->argms[i])
		{
			free((tl(cmds->content))->argms[i]);
			i++;
		}
		free((tl(cmds->content))->argms);
		free((tl(cmds->content))->cmd);
		free((tl(cmds->content)));
		free(cmds);
		cmds = tmp;
	}
	
}

int	main(int ac, char *av[], char **env)
{
	char		*line;
	t_lexer		*cur;
	t_list		*commands;
	t_expand	*envl;
	t_expand	*mini;

	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
    signal(SIGTSTP, SIG_IGN);
	if (ft_check_argms(ac, av))
		return (1);
	envl = ft_init_expander(env);
	mini = envl;
	while(mini)
	{
		if(ft_strcmp(mini->key, "SHLVL") == 0)
		{
			if(mini->value == NULL)
			{
				mini->value = ft_strdup(ft_itoa(1));
				if (!mini->value)
					return 1;
			}
			else 
				mini->value = ft_strdup(ft_itoa(ft_atoi(mini->value) + 1));
			// lvl++;
		}
		mini = mini->next;
	}
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
            ft_exec(commands);
			// ft_free_all_minishell(commands);
		}
	}
	return (0);
}
