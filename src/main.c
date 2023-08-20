/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:16:01 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/20 21:11:52 by yoel-bas         ###   ########.fr       */
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
	// free(g_minishell.str);
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

void	SHLVL(t_expand *envl)
{
	t_expand	*mini;
	int lvl = 0	;
	mini = envl;
	while(mini)
	{
		if(ft_strcmp(mini->key, "SHLVL") == 0)
		{
			if(ft_atoi(mini->value) < 0)
				mini->value = ft_strdup(ft_itoa(0));
			else if(ft_atoi(mini->value) == 999)
				mini->value = ft_strdup("");
			else if(mini->value == NULL)
				mini->value = ft_strdup(ft_itoa(1));
			else
				mini->value = ft_strdup(ft_itoa(ft_atoi(mini->value) + 1));
			lvl++;
		}
		mini = mini->next;
	}
	if(!lvl)
		ft_lexeradd_back_expnd(&envl, ft_lexernew_expnd("SHLVL", "1"));
}

int	main(int ac, char *av[], char **env)
{
	char		*line;
	t_lexer		*cur;
	t_list		*commands;
	t_expand	*envl;

	line = NULL;
	g_minishell.str = ft_strdup("");
	rl_catch_signals = 0;
	g_minishell.heredoc_executing = 1;
	g_minishell.stdin_backup = -1;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, SIG_IGN);
	if (ft_check_argms(ac, av))
		return (1);
	envl = ft_init_expander(env);
	SHLVL(envl);
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
