/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:16:01 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/30 22:29:14 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void ctrl_c_handler(int signum)
{
    (void)signum;
    printf("\nminishell$ ");
	fflush(stdout);
}

void ctrl_d_handler(int signum)
{
    (void)signum;
    printf("\nExiting minishell...\n");
    exit(0);
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
	t_list		*tmp;
	t_expand	*pp;

	rl_catch_signals = 0;
	signal(SIGINT, ctrl_c_handler);
    signal(SIGQUIT, SIG_IGN);
	if (ft_check_argms(ac, av))
		return (1);
	pp = ft_init_expander(env);
	while (1)
	{
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
		ft_expander(cur, pp, 1);
		tmp = ft_join_argms(&cur, pp);
		if (tmp)
			ft_exec(tmp, env);
	}
	return (0);
}
