/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_needs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:44:06 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/13 06:08:12 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_line_word(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\"'
		&& str[len] != '\'' && str[len] != '>'
		&& str[len] != '<' && str[len] != '|')
		len++;
	return (len);
}

t_lexer	*ft_lexernew(char *content, t_status status, t_type type)
{
	t_lexer	*node;

	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->type = type;
	node->status = status;
	node->value = ft_strdup(content);
	node->next = NULL;
	return (node);
}

void	ft_lexeradd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->next = NULL;
}

void	handle_word(t_lexer **tokenlist, char *line, int *i, t_status *s)
{
	char	*token;
	int		len;

	len = ft_line_word(&line[*i]);
	token = ft_substr(&line[*i], 0, len);
	ft_lexeradd_back(tokenlist, ft_lexernew(token, *s, WORD));
	free(token);
	(*i) += len;
}
