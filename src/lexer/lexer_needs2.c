/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_needs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 04:24:23 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/19 01:17:22 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirection(t_lexer **tokenlist, char *line, int *i, t_status *s)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		ft_lexeradd_back(tokenlist, ft_lexernew(">>", *s, DREDIR_OUT));
		(*i) += 2;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		ft_lexeradd_back(tokenlist, ft_lexernew("<<", *s, HERE_DOC));
		(*i) += 2;
	}
}

void	handle_special_characters(t_lexer **tokenlist, char *line, int *i,
		t_status *s)
{
	if (line[*i] == '|')
	{
		ft_lexeradd_back(tokenlist, ft_lexernew("|", *s, PIPE_LINE));
		(*i) += 1;
	}
	else if (line[*i] == '>')
	{
		ft_lexeradd_back(tokenlist, ft_lexernew(">", *s, REDIR_OUT));
		(*i) += 1;
	}
	else if (line[*i] == '<')
	{
		ft_lexeradd_back(tokenlist, ft_lexernew("<", *s, REDIR_IN));
		(*i) += 1;
	}
	ft_handle_white_space(tokenlist, line, i, *s);
}

void	handle_double_quote(t_lexer **tokenlist, char *line, int *i,
		t_status *s)
{
	if (line[*i] == '\"')
	{
		if (line[*i] == '\"' && line[*i + 1] == '\"' && *s == GENERAL)
		{
			g_minishell.err = 1;
			ft_lexeradd_back(tokenlist, ft_lexernew("", GENERAL, WORD));
			(*i) += 1;
		}
		else if (*s == GENERAL)
		{
			*s = IN_DQUOTE;
			ft_lexeradd_back(tokenlist, ft_lexernew("\"", GENERAL,
					DOUBLE_QUOTE));
		}
		else if (*s == IN_DQUOTE)
		{
			*s = GENERAL;
			ft_lexeradd_back(tokenlist, ft_lexernew("\"", GENERAL,
					DOUBLE_QUOTE));
		}
		else
			ft_lexeradd_back(tokenlist, ft_lexernew("\"", IN_QUOTE,
					DOUBLE_QUOTE));
		(*i) += 1;
	}
}

void	handle_quote(t_lexer **tokenlist, char *line, int *i, t_status *s)
{
	if (line[*i] == '\'')
	{
		if (line[*i] == '\'' && line[*i + 1] == '\'' && *s == GENERAL)
		{
			g_minishell.err = 1;
			ft_lexeradd_back(tokenlist, ft_lexernew("", GENERAL, WORD));
			(*i) += 1;
		}
		else if (*s == GENERAL)
		{
			ft_lexeradd_back(tokenlist, ft_lexernew("\'", *s, QOUTE));
			*s = IN_QUOTE;
		}
		else if (*s == IN_QUOTE)
		{
			*s = GENERAL;
			ft_lexeradd_back(tokenlist, ft_lexernew("\'", *s, QOUTE));
		}
		else
			ft_lexeradd_back(tokenlist, ft_lexernew("\'", *s, QOUTE));
		(*i) += 1;
	}
}

void	handle_env(t_lexer **tokenlist, char *line, int *i, t_status *s)
{
	int		len;
	char	*token;

	if (line[*i] == '$' && line[*i + 1] != '$')
	{
		if (line[*i + 1] == '\"')
			(*i) += 1;
		len = ft_line_env(&line[*i]);
		token = ft_substr(&line[*i], 0, len);
		ft_lexeradd_back(tokenlist, ft_lexernew(token, *s, ENV));
		free(token);
		(*i) += len;
	}
}
