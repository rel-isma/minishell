/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_needs_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:34:00 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/13 20:37:41 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	special_variables_1(t_lexer **tokenlist, char *line, int *i,
		t_status *s)
{
	if (line[*i] == '$' && line[*i + 1] == '$')
	{
		ft_lexeradd_back(tokenlist, ft_lexernew("$$", *s, ENV));
		(*i) += 2;
	}
	else if (line[*i] == '$' && line[*i + 1] == '0')
	{
		ft_lexeradd_back(tokenlist, ft_lexernew("$0", *s, ENV));
		(*i) += 2;
	}
	else if (line[*i] == '$' && line[*i + 1] == '*')
	{
		ft_lexeradd_back(tokenlist, ft_lexernew("$*", *s, ENV));
		(*i) += 2;
	}
	else if (line[*i] == '$' && line[*i + 1] == '#')
	{
		ft_lexeradd_back(tokenlist, ft_lexernew("$#", *s, ENV));
		(*i) += 2;
	}
	else if (line[*i] == '$' && line[*i + 1] == '?')
	{
		ft_lexeradd_back(tokenlist, ft_lexernew("$?", *s, ENV));
		(*i) += 2;
	}
}

void	special_variables_2(t_lexer **tokenlist, char *line, int *i,
		t_status *s)
{
	if (line[*i] == '$' && line[*i + 1] == '!')
	{
		ft_lexeradd_back(tokenlist, ft_lexernew("$!", *s, ENV));
		(*i) += 2;
	}
	else if (line[*i] == '$' && line[*i + 1] == '@')
	{
		ft_lexeradd_back(tokenlist, ft_lexernew("$@", *s, ENV));
		(*i) += 2;
	}
	else if (line[*i] == '$' && line[*i + 1] == '-')
	{
		ft_lexeradd_back(tokenlist, ft_lexernew("$-", *s, ENV));
		(*i) += 2;
	}
	else if (line[*i] == '$' && (line[*i + 1] >= '1' && line[*i + 1] <= '9'))
	{
		ft_lexeradd_back(tokenlist, ft_lexernew("$5", *s, ENV));
		(*i) += 2;
	}
}
