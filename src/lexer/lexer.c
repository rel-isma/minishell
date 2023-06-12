/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:44:37 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/12 16:44:17 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void *ft_lexer(char *line)
{
	t_lexer *tokenlist = NULL;

	int i = 0;
	while (line[i] != '\0')
	{
		if(line[i] == '>' && line[i + 1] == '>')
		{
			ft_lexeradd_back(&tokenlist, ft_lexernew(">>", GENERAL, DREDIR_OUT));
			i++;
		} 
		else if(line[i] == '<' && line[i + 1] == '<')
		{
            ft_lexeradd_back(&tokenlist, ft_lexernew("<<", GENERAL, HERE_DOC));
			i++;
		}
        else if (line[i] == '|')
            ft_lexeradd_back(&tokenlist, ft_lexernew("|", GENERAL, PIPE_LINE));
        else if (line[i] == '>')
            ft_lexeradd_back(&tokenlist, ft_lexernew(">", GENERAL, REDIR_OUT));
        else if (line[i] == '<')
            ft_lexeradd_back(&tokenlist, ft_lexernew("<", GENERAL, REDIR_IN));
        else if (line[i] == '\'' && line[i + 1] == '\'')
        {
            ft_lexeradd_back(&tokenlist, ft_lexernew("\"", GENERAL, DOUBLE_QUOTE));
            i++;
        }
        else if (line[i] == '\'')
            ft_lexeradd_back(&tokenlist, ft_lexernew("\'", GENERAL, QOUTE));
        else if (line[i] == ' ')
            ft_lexeradd_back(&tokenlist, ft_lexernew(" ", GENERAL, WHITE_SPACE));
        else if ()
		i++;
	}
    return (NULL);
}
