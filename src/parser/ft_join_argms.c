/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_argms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:41:16 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/13 15:31:26 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_delete_double_quote(t_lexer **lst)
{
	t_lexer	*cur = *lst;
	t_lexer *next = NULL;
	t_lexer *prev = NULL;

	while (cur)
	{
		if(cur->type == DOUBLE_QUOTE && cur->status == WORD)
		{
			next = cur->next;
			if (prev)
				prev->next = next;
			else
				*lst = next;
			free(cur->value);
			free(cur);
		}
		else
			prev = cur;
		cur = cur->next;
	}
}

void ft_delete_quote(t_lexer **lst)
{
	t_lexer	*cur = *lst;
	t_lexer *next = NULL;
	t_lexer *prev = NULL;

	while (cur)
	{
		if(cur->type == QOUTE && cur->status == WORD)
		{
			next = cur->next;
			if (prev)
				prev->next = next;
			else
				*lst = next;
			free(cur->value);
			free(cur);
		}
		else
			prev = cur;
		cur = cur->next;
	}
}

t_parser	*ft_parsernew(char *content)
{
	t_parser	*node;

	node = (t_parser *)malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	node->value = ft_strdup(content);
	node->next = NULL;
	return (node);
}

void	ft_parseradd_back(t_parser **lst, t_parser *new)
{
	t_parser	*last;

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
t_parser    *ft_join_cmd(t_lexer **lst)
{
	t_lexer *cur = *lst;
	t_parser *new;
	char *str = ft_strdup("");
	char *tmp;

	while (cur)
	{
		while (cur && cur->type != WHITE_SPACE)
		{
			tmp = str;
			str = ft_strjoin(str, cur->value);
			free(tmp);
			cur = cur->next;
		}
		ft_parseradd_back(&new, ft_parsernew(str));
		if (cur && cur->type == WHITE_SPACE)
		{
			free(str);
			str = ft_strdup("");
			ft_parseradd_back(&new, ft_parsernew(" "));
			cur = cur->next;
		}
	}
	return (new);
}

t_parser	*ft_join_argms(t_lexer **lst)
{
	t_parser *tok_new;
	ft_delete_double_quote(lst);
	ft_delete_quote(lst);
	tok_new = ft_join_cmd(lst);
	return (tok_new);
}
