/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:15:02 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/16 16:28:55 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_syntax(t_lexer *lst)
{
	int d;
	t_lexer *cur;

	d = 0;
	cur = lst;
	while (lst)
	{
		if (lst->type == DOUBLE_QUOTE && lst->status == GENERAL)
			d++;
		lst = lst->next;
	}
	if (d % 2 != 0)
	{
		printf("minishell: syntax error near unexpected token `\"`\n");
		return (1);
	}
	d = 0;
	while (cur)
	{
		if (cur->type == QOUTE && cur->status == GENERAL)
			d++;
		cur = cur->next;
	}
	if (d % 2 != 0)
	{
		printf("minishell: syntax error near unexpected token `\'`\n");
		return (1);
	}
	return (0);
}

void	ft_syntax_errors(t_lexer *token_lst)
{
	t_lexer *current;

	current = token_lst;
	if (ft_check_syntax(current))
		return ;
	
}