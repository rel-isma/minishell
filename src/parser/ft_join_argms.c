/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_argms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:41:16 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/14 21:39:55 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_delete_double_quote(t_lexer **lst)
{
	t_lexer	*cur;
	t_lexer	*next;
	t_lexer	*prev;

	cur = *lst;
	next = NULL;
	prev = NULL;
	while (cur)
	{
		if (cur->type == DOUBLE_QUOTE && cur->status == WORD)
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

void	ft_delete_quote(t_lexer **lst)
{
	t_lexer	*cur;
	t_lexer	*next;
	t_lexer	*prev;

	cur = *lst;
	next = NULL;
	prev = NULL;
	while (cur)
	{
		if (cur->type == QOUTE && cur->status == WORD)
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

t_parser	*ft_parsernew(char *content, int flg)
{
	t_parser	*node;

	if (!*content && flg)
		return NULL;
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

int	check_no_word(t_lexer *lst)
{
	if ((lst->type == WHITE_SPACE && (lst->status == IN_DQUOTE
				|| lst->status == IN_QUOTE)) || (lst->type == PIPE_LINE && (lst->status == IN_DQUOTE
				|| lst->status == IN_QUOTE)) || (lst->type == HERE_DOC && (lst->status == IN_DQUOTE
				|| lst->status == IN_QUOTE)) || (lst->type == DREDIR_OUT && (lst->status == IN_DQUOTE
				|| lst->status == IN_QUOTE)) || (lst->type == REDIR_IN && (lst->status == IN_DQUOTE
				|| lst->status == IN_QUOTE)) || (lst->type == REDIR_OUT && (lst->status == IN_DQUOTE
				|| lst->status == IN_QUOTE)) || ((lst->type != WHITE_SPACE) && lst->type != PIPE_LINE
			&& lst->type != REDIR_IN && lst->type != REDIR_OUT
			&& lst->type != HERE_DOC && lst->type != DREDIR_OUT))
	{
		return (1);
	}
	else
		return (0);
}
t_parser	*ft_join_cmd(t_lexer **lst)
{
	t_lexer		*cur;
	t_parser	*new;
	char		*str;
	char		*tmp;
	int flg		= 1;

	cur = *lst;
	new = NULL;
	str = ft_strdup("");
	while (cur)
	{
		while (cur && check_no_word(cur))
		{
			if (!*cur->value)
				flg = 0;
			tmp = str;
			str = ft_strjoin(str, cur->value);
			free(tmp);
			cur = cur->next;
		}
		ft_parseradd_back(&new, ft_parsernew(str, flg));
		if (cur && (!check_no_word(cur)))
		{
			free(str);
			str = ft_strdup("");
			ft_parseradd_back(&new, ft_parsernew(cur->value, 0));
			cur = cur->next;
		}
	}
	return (new);
}

t_parser	*ft_join_argms(t_lexer **lst)
{
	t_parser	*tok_new;

	ft_delete_double_quote(lst);
	ft_delete_quote(lst);
	tok_new = ft_join_cmd(lst);
	return (tok_new);
}
