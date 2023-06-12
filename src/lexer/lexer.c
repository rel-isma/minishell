/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:44:37 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/12 22:53:28 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_line_word(char *str)
{
    int     len = 0;

    while (str[len] && str[len] != ' ' && str[len] != '\"' 
            && str[len] != '\''  && str[len] != '>' 
            && str[len] != '<' && str[len] != '|')
        len++;
    return len;

}

void *ft_lexer(char *line)
{
	t_lexer *tokenlist = NULL;
    t_status s;
    // char *ll;
    int len = 0;

	int i = 0;
    s = GENERAL;
	while (line[i] != '\0')
	{
		if(line[i] == '>' && line[i + 1] == '>')
		{
			ft_lexeradd_back(&tokenlist, ft_lexernew(">>", s, DREDIR_OUT));
			i++;
		} 
		else if(line[i] == '<' && line[i + 1] == '<')
		{
            ft_lexeradd_back(&tokenlist, ft_lexernew("<<", s, HERE_DOC));
			i++;
		}
        else if (line[i] == '|')
        {
            ft_lexeradd_back(&tokenlist, ft_lexernew("|", s, PIPE_LINE));
            i++;
        }
        else if (line[i] == '>')
        {
            ft_lexeradd_back(&tokenlist, ft_lexernew(">", s, REDIR_OUT));
            i++;
        }
        else if (line[i] == '<')
        {
            ft_lexeradd_back(&tokenlist, ft_lexernew("<", s, REDIR_IN));
            i++;
        }
        else if (line[i] == '\"')
        {
            if (s == GENERAL)
            {
                s = IN_DQUOTE;
                ft_lexeradd_back(&tokenlist, ft_lexernew("\"", GENERAL, DOUBLE_QUOTE));
                }
            else if (s == IN_DQUOTE)
            {
                s = GENERAL;
                ft_lexeradd_back(&tokenlist, ft_lexernew("\"", GENERAL, DOUBLE_QUOTE));
                }
            else
                ft_lexeradd_back(&tokenlist, ft_lexernew("\"", IN_QUOTE, DOUBLE_QUOTE));
            i++;
        }
        else if (line[i] == '\'')
        {
            if (s == GENERAL)
            {
                ft_lexeradd_back(&tokenlist, ft_lexernew("\'", s, QOUTE));
                s = IN_QUOTE;
                }
            else if (s == IN_QUOTE)
            {
                s = GENERAL;
                ft_lexeradd_back(&tokenlist, ft_lexernew("\'", s, QOUTE));
                }
            else
                ft_lexeradd_back(&tokenlist, ft_lexernew("\'", s, QOUTE));
            i++;
        }
        else if (line[i] == ' ')
        {
            ft_lexeradd_back(&tokenlist, ft_lexernew(" ", s, WHITE_SPACE));
            i++;
        }
        else if (line[i] == '$')
        {
            len = ft_line_word(&line[i]);
            ft_lexeradd_back(&tokenlist, ft_lexernew(ft_substr(&line[i], 0, len), s, ENV));
            i += len;
        }
        else
        {
            len = ft_line_word(&line[i]);
            ft_lexeradd_back(&tokenlist, ft_lexernew(ft_substr(&line[i], 0, len), s, WORD));
            i += len;
        }
	}
    
    while (tokenlist)
    {
        printf("Content = |%s|,   state = %d, type = %d\n", tokenlist->value, tokenlist->status, tokenlist->type);
        tokenlist = tokenlist->next;
    }
    
    return (NULL);
}
