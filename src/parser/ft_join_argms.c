/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_argms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:41:16 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/11 17:09:47 by rel-isma         ###   ########.fr       */
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

void	ft_join_cmd(t_lexer **lst)
{
	t_lexer	*cur = *lst;

	while (cur)
	{
		if (cur->type != WHITE_SPACE)
		{
			printf("%s", cur->value);
		}
		cur = cur->next;
	}
	printf("\n");
}

void ft_join_argms(t_lexer **lst)
{
	ft_delete_double_quote(lst);
	ft_delete_quote(lst);
	ft_join_cmd(lst);
}
