/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:16:01 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/18 01:24:24 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fu(void)
{
	system("leaks minishell");
}

int	main(int ac, char *av[], char **env)
{
	char		*line;
	t_lexer		*cur;
	t_expand	*pp;
	t_cmd	*tmp;
	t_cmd	*tm;
	int i;

	atexit(fu);
	(void)av;
	if (ac != 1)
	{
		printf("Error : just like this please \n\t 👉👉 ./minishell 👈👈\n");
		return (0);
	}
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			return (0);
		add_history(line);
		cur = ft_lexer(line);
		ft_syntax_errors(cur);
		pp = ft_expander(cur, env);
		tmp = ft_join_argms(&cur);
		/// had {{ tmp }} how li tkhdm bih how fih cmd and file and argms
		tm = tmp;
		while (tm)
		{
			i = 0;
			printf("cmd->\t[%s]\t infile [%d]\t oufile [%d]\t", tm->cmd,
				tm->infile, tm->oufile);
			while (tm->argms[i])
			{
				printf("arg->\t[%s]\t", tm->argms[i]);
				i++;
			}
			printf("\n");
			tm = tm->next;
		}
		ft_free_list(cur);
		ft_free_list_exp(pp);
		ft_free_list_cmd(tmp);
	}
	return (0);
}
