/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_stx_qoute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:03:15 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/23 18:19:06 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_d_qoute(t_lexer *lst)
{
	int		d;
	t_lexer	*cur;

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
		ft_putstr_fd("minishell: syntax error near unexpected token `\"`\n", 2);
		g_minishell.exit_code = 258;
		return (1);
	}
	return (0);
}

int	check_s_qoute(t_lexer *lst)
{
	int		d;
	t_lexer	*cur;

	d = 0;
	cur = lst;
	while (cur)
	{
		if (cur->type == QOUTE && cur->status == GENERAL)
			d++;
		cur = cur->next;
	}
	if (d % 2 != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `\'`\n", 2);
		g_minishell.exit_code = 258;
		return (1);
	}
	return (0);
}

int	ft_check_syntax_qoute(t_lexer *lst)
{
	if (check_d_qoute(lst))
		return (1);
	if (check_s_qoute(lst))
		return (1);
	return (0);
}
