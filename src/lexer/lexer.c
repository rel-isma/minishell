/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:44:37 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/13 23:42:34 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_lexer(char *line)
{
	t_lexer		*tokenlist;
	//t_lexer		*tmp;
	t_status	s;
	int			i;

	i = 0;
	s = GENERAL;
	tokenlist = NULL;
	while (line[i] != '\0')
	{
		if ((line[i] == ' ' || line[i] == '\"' || line[i] == 36
				|| line[i] == '\'' || line[i] == '>'
				|| line[i] == '<' || line[i] == '|'))
		{
			handle_redirection(&tokenlist, line, &i, &s);
			handle_special_characters(&tokenlist, line, &i, &s);
			handle_double_quote(&tokenlist, line, &i, &s);
			handle_quote(&tokenlist, line, &i, &s);
			special_variables_1(&tokenlist, line, &i, &s);
			special_variables_2(&tokenlist, line, &i, &s);
			handle_env(&tokenlist, line, &i, &s);
		}
		else
			handle_word(&tokenlist, line, &i, &s);
	}
	// tmp = tokenlist;
	// while (tmp)
	// {
	// 	printf("Content =   |%s|,     state = %d,     type = %d\n",
	// 		tmp->value, tmp->status, tmp->type);
	// 	tmp = tmp->next;
	// }
	ft_syntax_errors(tokenlist);
	ft_free_list(tokenlist);
	free(line);
	return (NULL);
}
