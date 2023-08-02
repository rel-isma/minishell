/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delele_dqu_qu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 23:18:07 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/02 16:55:47 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_delete_double_quote(t_lexer **lst)
{
	t_lexer	*cur;
	t_lexer	*next;
	t_lexer	*prev;

	cur = *lst;
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
			cur = next;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

void	ft_delete_quote(t_lexer **lst)
{
	t_lexer	*cur;
	t_lexer	*next;
	t_lexer	*prev;

	cur = *lst;
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
			cur = next;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}
