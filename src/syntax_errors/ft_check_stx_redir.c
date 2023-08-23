/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_stx_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:04:34 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/23 18:19:37 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_herd(t_lexer *lst, int flg)
{
	return (flg == 1 && ((lst && lst->type != WORD && lst->type != DOUBLE_QUOTE
				&& lst->type != QOUTE && lst->type != ENV
				&& lst->status == GENERAL) || !lst));
}

int	ft_check_stx_redir_out(t_lexer *cur)
{
	t_lexer	*lst;
	int		flg;

	lst = cur;
	flg = 0;
	while (lst)
	{
		if (lst->type == REDIR_OUT && lst->status == GENERAL)
		{
			flg = 1;
			lst = lst->next;
		}
		if (lst && lst->type == WHITE_SPACE && lst->status == GENERAL
			&& flg == 1)
			lst = lst->next;
		if (ft_check_herd(lst, flg))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `>`\n", 2);
			return (g_minishell.exit_code = 258, 1);
		}
		else if (flg)
			flg = 0;
		lst = lst->next;
	}
	return (0);
}

int	ft_check_stx_redir_in(t_lexer *cur)
{
	t_lexer	*lst;
	int		flg;

	lst = cur;
	flg = 0;
	while (lst)
	{
		if (lst->type == REDIR_IN && lst->status == GENERAL)
		{
			flg = 1;
			lst = lst->next;
		}
		if (lst && lst->type == WHITE_SPACE && lst->status == GENERAL
			&& flg == 1)
			lst = lst->next;
		if (ft_check_herd(lst, flg))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `<`\n", 2);
			return (g_minishell.exit_code = 258, 1);
		}
		else if (flg)
			flg = 0;
		lst = lst->next;
	}
	return (0);
}

int	ft_check_stx_apend(t_lexer *cur)
{
	t_lexer	*lst;
	int		flg;

	lst = cur;
	flg = 0;
	while (lst)
	{
		if (lst->type == DREDIR_OUT && lst->status == GENERAL)
		{
			flg = 1;
			lst = lst->next;
		}
		if (lst && flg == 1 && lst->type == WHITE_SPACE
			&& lst->status == GENERAL)
			lst = lst->next;
		if (ft_check_herd(lst, flg))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `>>`\n", 2);
			return (g_minishell.exit_code = 258, 1);
		}
		else if (flg)
			flg = 0;
		lst = lst->next;
	}
	return (0);
}

int	ft_check_stx_heredoc(t_lexer *cur)
{
	t_lexer	*lst;
	int		flg;

	lst = cur;
	flg = 0;
	while (lst)
	{
		if (lst->type == HERE_DOC && lst->status == GENERAL)
		{
			flg = 1;
			lst = lst->next;
		}
		if (lst && flg == 1 && lst->type == WHITE_SPACE
			&& lst->status == GENERAL)
			lst = lst->next;
		if (ft_check_herd(lst, flg))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `<<`\n", 2);
			return (g_minishell.exit_code = 258, 1);
		}
		else if (flg)
			flg = 0;
		lst = lst->next;
	}
	return (0);
}
