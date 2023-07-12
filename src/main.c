/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:16:01 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/21 11:04:13 by rel-isma         ###   ########.fr       */
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

	//atexit(fu);
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
		ft_join_argms(&cur);
		/*t_lexer		*tmp = cur;
		while (tmp)
		{
			printf("Content =   |%s|,     state = %d,     type = %d\n",
		 		tmp->value, tmp->status, tmp->type);
			tmp = tmp->next;
		}*/
		ft_free_list(cur);
		ft_free_list_exp(pp);
	}
	return (0);
}
