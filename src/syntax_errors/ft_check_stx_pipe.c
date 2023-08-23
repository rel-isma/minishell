/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_stx_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:03:07 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/23 15:47:37 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check(t_lexer *lst, int flg)
{
	return (flg == 1 && ((lst && lst->type != WORD && lst->type != DOUBLE_QUOTE
				&& lst->type != QOUTE && lst->type != ENV
				&& lst->type != REDIR_IN && lst->type != REDIR_OUT
				&& lst->type != HERE_DOC && lst->type != DREDIR_OUT
				&& lst->status == GENERAL) || !lst));
}

static int	ft_check_frist(t_lexer *lst)
{
	if (lst && lst->type == WHITE_SPACE && lst->status == GENERAL)
		lst = lst->next;
	if (lst && lst->type == PIPE_LINE && lst->status == GENERAL)
	{
		printf("minishell: syntax error near unexpected token `|`\n");
		g_minishell.exit_code = 258;
		return (1);
	}
	return (0);
}

int	printf_er(void)
{
	printf("minishell: syntax error near unexpected token `|`\n");
	g_minishell.exit_code = 258;
	return (1);
}

int	ft_check_syntax_pipe(t_lexer *cur)
{
	t_lexer	*lst;
	int		flg;

	lst = cur;
	flg = 0;
	if (ft_check_frist(lst))
		return (1);
	while (lst)
	{
		if (lst->type == PIPE_LINE && lst->status == GENERAL)
		{
			flg = 1;
			lst = lst->next;
		}
		if (lst && lst->type == WHITE_SPACE && lst->status == GENERAL
			&& flg == 1)
			lst = lst->next;
		if (ft_check(lst, flg))
			return (printf_er());
		else if (flg)
			flg = 0;
		lst = lst->next;
	}
	return (0);
}
