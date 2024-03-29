/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_needs_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:34:00 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/28 02:54:23 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	special_variables_1(t_lexer **tokenlist, char *line, int *i,
		t_status *s)
{
	if (line[*i] == '$' && line[*i + 1] == '$')
	{
		ft_l_back(tokenlist, ft_lexernew("$$", *s, ENV));
		(*i) += 2;
	}
	else if (line[*i] == '$' && line[*i + 1] == '0')
	{
		ft_l_back(tokenlist, ft_lexernew("$0", *s, ENV));
		(*i) += 2;
	}
	else if (line[*i] == '$' && line[*i + 1] == '*')
	{
		ft_l_back(tokenlist, ft_lexernew("$*", *s, ENV));
		(*i) += 2;
	}
	else if (line[*i] == '$' && line[*i + 1] == '#')
	{
		ft_l_back(tokenlist, ft_lexernew("$#", *s, ENV));
		(*i) += 2;
	}
	else if (line[*i] == '$' && line[*i + 1] == '?')
	{
		ft_l_back(tokenlist, ft_lexernew("$?", *s, ENV));
		(*i) += 2;
	}
}

void	ft_help_var(char *line, int *i)
{
	if (line[*i] == '$' && (line[*i + 1] == '\"'
			|| line[*i + 1] == '\"') && line[*i - 1] != '\"')
		(*i) += 1;
	else if (line[*i] == '$' && (line[*i + 1] == '\''
			|| line[*i + 1] == '\'') && line[*i - 1] != '\'')
		(*i) += 1;
}

void	special_variables_2(t_lexer **tokenlist, char *line, int *i,
		t_status *s)
{
	char	*str;

	ft_help_var(line, i);
	if (line[*i] == '$' && line[*i + 1] == '!')
	{
		ft_l_back(tokenlist, ft_lexernew("$!", *s, ENV));
		(*i) += 2;
	}
	else if (line[*i] == '$' && line[*i + 1] == '@')
	{
		ft_l_back(tokenlist, ft_lexernew("$@", *s, ENV));
		(*i) += 2;
	}
	else if (line[*i] == '$' && line[*i + 1] == '-')
	{
		ft_l_back(tokenlist, ft_lexernew("$-", *s, ENV));
		(*i) += 2;
	}
	else if (line[*i] == '$' && (line[*i + 1] >= '1' && line[*i + 1] <= '9'))
	{
		str = ft_substr(&line[*i], 0, 2);
		ft_l_back(tokenlist, ft_lexernew(str, *s, ENV));
		return ((*i) += 2, free(str));
	}
}

void	handle_redirection(t_lexer **tokenlist, char *line, int *i, t_status *s)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		ft_l_back(tokenlist, ft_lexernew(">>", *s, DREDIR_OUT));
		(*i) += 2;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		ft_l_back(tokenlist, ft_lexernew("<<", *s, HERE_DOC));
		(*i) += 2;
	}
}

void	ft_handle_white_space(t_lexer **tokenlist, char *line, int *i,
		t_status s)
{
	char	str[2];

	if (white_space(line[*i]))
	{
		str[0] = line[*i];
		str[1] = '\0';
		ft_l_back(tokenlist, ft_lexernew(str, s, WHITE_SPACE));
		(*i) += 1;
		if (s == GENERAL)
		{
			while (white_space(line[*i]))
				(*i) += 1;
		}
	}
}
