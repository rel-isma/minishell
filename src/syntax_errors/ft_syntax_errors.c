/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:15:02 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/18 02:38:45 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	else
		return (0);
}

int	ft_syntax_errors(t_lexer *token_lst)
{
	t_lexer	*current;

	current = token_lst;
	if (ft_check_syntax_qoute(current))
		return (1);
	else if (ft_check_syntax_redir(current))
		return (1);
	else if (ft_check_syntax_pipe(current))
		return (1);
	else
		return (0);
}
