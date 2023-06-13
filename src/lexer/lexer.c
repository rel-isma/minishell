/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:44:37 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/13 02:53:50 by rel-isma         ###   ########.fr       */
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

void    handle_redirection(t_lexer **tokenlist, char *line, int *i, t_status *s)
{
    if(line[*i] == '>' && line[*i + 1] == '>')
    {
        ft_lexeradd_back(tokenlist, ft_lexernew(">>", *s, DREDIR_OUT));
        (*i) += 2;
    } 
    else if(line[*i] == '<' && line[*i + 1] == '<')
    {
        ft_lexeradd_back(tokenlist, ft_lexernew("<<", *s, HERE_DOC));
        (*i) += 2;
    }
}
void    handle_special_characters(t_lexer **tokenlist, char *line, int *i, t_status *s)
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
    else if (line[*i] == ' ')
    {
        ft_lexeradd_back(tokenlist, ft_lexernew(" ", *s, WHITE_SPACE));
        (*i) += 1;
    }
}

void    handle_double_quote(t_lexer **tokenlist, char *line, int *i, t_status *s)
{
    if (line[*i] == '\"')
    {
        if (*s == GENERAL)
        {
            *s = IN_DQUOTE;
            ft_lexeradd_back(tokenlist, ft_lexernew("\"", GENERAL, DOUBLE_QUOTE));
        }
        else if (*s == IN_DQUOTE)
        {
            *s = GENERAL;
            ft_lexeradd_back(tokenlist, ft_lexernew("\"", GENERAL, DOUBLE_QUOTE));
        }
        else
            ft_lexeradd_back(tokenlist, ft_lexernew("\"", IN_QUOTE, DOUBLE_QUOTE));
        (*i) += 1;
    }
  
}
void    handle_quote(t_lexer **tokenlist, char *line, int *i, t_status *s)
{
    if (line[*i] == '\'')
    {
        if (*s == GENERAL)
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

void    handle_env(t_lexer **tokenlist, char *line, int *i, t_status *s)
{
    int len;

    if (line[*i] == '$')
    {
        len = ft_line_word(&line[*i]);
        ft_lexeradd_back(tokenlist, ft_lexernew(ft_substr(&line[*i], 0, len), *s, ENV));
        (*i) += len;
    }
}

void handle_word(t_lexer **tokenlist, char *line, int *i, t_status *s)
{
    int len;

    len = ft_line_word(&line[*i]);
    printf("\nlen == [%d]\n", len);
    ft_lexeradd_back(tokenlist, ft_lexernew(ft_substr(&line[*i], 0, len), *s, WORD));
    (*i) += len;

}
// ls -la | "$USR" |

void *ft_lexer(char *line)
{
	t_lexer *tokenlist = NULL;
    t_status s;

	int i = 0;
    s = GENERAL;
	while (line[i] != '\0')
	{
        if((line[i] == ' ' || line[i] == '\"' || line[i] == '\''  || line[i] == '>' || line[i] == '<' || line[i] == '|'))
        {
            handle_redirection(&tokenlist, line, &i, &s);
            handle_special_characters(&tokenlist, line, &i, &s);
            handle_double_quote(&tokenlist, line, &i, &s);
            handle_quote(&tokenlist, line, &i, &s);
            handle_env(&tokenlist, line, &i, &s);
        }
        else
            handle_word(&tokenlist, line, &i, &s);
	}
    // while (tokenlist)
    // {
    //     printf("Content =   |%s|,     state = %d,     type = %d\n", tokenlist->value, tokenlist->status, tokenlist->type);
    //     tokenlist = tokenlist->next;
    // }
    return (NULL);
}
