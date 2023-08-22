/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:44:37 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/22 03:08:31 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_env(t_lexer **tokenlist, char *line, int *i, t_status *s)
{
	int		len;
	char	*token;

	if (line[*i] == '$' && line[*i + 1] != '$' && line[*i + 1] != '?')
	{
		printf("[[%s]]\n", &line[*i]);
		len = ft_line_env(&line[*i]);
		token = ft_substr(&line[*i], 0, len);
		ft_lexeradd_back(tokenlist, ft_lexernew(token, *s, ENV));
		free(token);
		(*i) += len;
	}
}

int	white_space(char str)
{
	if (str == ' ' || str == '\t' || str == '\n' || str == '\f' || str == '\r'
		|| str == '\v')
		return (1);
	else
		return (0);
}

t_lexer	*ft_lexer(char *line)
{
	t_lexer		*tokenlist;
	t_status	s;
	int			i;

	i = 0;
	s = GENERAL;
	tokenlist = NULL;
	while (line[i] != '\0')
	{
		if ((white_space(line[i]) || line[i] == '\"' || line[i] == 36
				|| line[i] == '\'' || line[i] == '>' || line[i] == '<'
				|| line[i] == '|'))
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
	return (free(line), tokenlist);
}
