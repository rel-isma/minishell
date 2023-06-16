/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:16:01 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/13 20:59:38 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fu(void)
{
	system("leaks minishell");
}

int	main(int ac, char *av[], char **env)
{
	char	*line;
	// atexit(fu);
	(void) av;
	(void) env;
	if (ac != 1)
		printf("rak dkhlti ktr mn arg\n");
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			return (0);
		add_history(line);
		ft_lexer(line);
	}
	return (0);
}
