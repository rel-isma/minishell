/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:15:02 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/16 17:43:46 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_check_stx_redir_out(t_lexer *cur)
{
	int	flg;
	t_lexer *lst;

	lst = cur;
	flg = 0;
	while (lst)
	{
		if (lst->type == REDIR_OUT && lst->status == GENERAL)
		{
			flg = 1;
			lst = lst->next;
		}
		if (lst && lst->type == WHITE_SPACE && lst->status == GENERAL && flg == 1)
			lst = lst->next;
		if (flg == 1 && ((lst && lst->type != WORD && lst->status == GENERAL)|| !lst))
		{
			printf("minishell: syntax error near unexpected token `>`\n");
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int ft_check_stx_redir_in(t_lexer *cur)
{
	int	flg;
	t_lexer *lst;

	lst = cur;
	flg = 0;
	while (lst)
	{
		if (lst->type == REDIR_IN && lst->status == GENERAL)
		{
			flg = 1;
			lst = lst->next;
		}
		if (lst && lst->type == WHITE_SPACE && lst->status == GENERAL && flg == 1)
			lst = lst->next;
		if (flg == 1 && ((lst && lst->type != WORD && lst->status == GENERAL)|| !lst))
		{
			printf("minishell: syntax error near unexpected token `<`\n");
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int ft_check_stx_apend(t_lexer *cur)
{
	int	flg;
	t_lexer *lst;

	lst = cur;
	flg = 0;
	while (lst)
	{
		if (lst->type == DREDIR_OUT && lst->status == GENERAL)
		{
			flg = 1;
			lst = lst->next;
		}
		if (lst && flg == 1 && lst->type == WHITE_SPACE && lst->status == GENERAL)
			lst = lst->next;
		if (flg == 1 && ((lst && lst->type != WORD && lst->status == GENERAL)|| !lst))
		{
			printf("minishell: syntax error near unexpected token `>>`\n");
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int ft_check_stx_heredoc(t_lexer *cur)
{
	int	flg;
	t_lexer *lst;

	lst = cur;
	flg = 0;
	while (lst)
	{
		if (lst->type == HERE_DOC && lst->status == GENERAL)
		{
			flg = 1;
			lst = lst->next;
		}
		if (lst && flg == 1 && lst->type == WHITE_SPACE && lst->status == GENERAL)
			lst = lst->next;
		if (flg == 1 && ((lst && lst->type != WORD && lst->status == GENERAL)|| !lst))
		{
			printf("minishell: syntax error near unexpected token `<<`\n");
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_check_syntax_redir(t_lexer *lst)
{
	if (ft_check_stx_apend(lst))
		return (1);
	if (ft_check_stx_heredoc(lst))
		return (1);
	if (ft_check_stx_redir_out(lst))
		return (1);
	if (ft_check_stx_redir_in(lst))
		return (1);
	return (0);
}

int	ft_check_syntax_qoute(t_lexer *lst)
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
	if (ft_check_syntax_qoute(current))
		return ;
	current = token_lst;
	if (ft_check_syntax_redir(current))
		return ;
}