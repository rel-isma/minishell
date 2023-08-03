/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:41:38 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/03 11:05:46 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	ft_len(t_parser *cur)
{
	int	len;

	len = 0;
	if (cur && cur->type == PIPE_LINE)
		cur = cur->next;
	while (cur && cur->type != PIPE_LINE)
	{
		if (cur && (cur->type == REDIR_IN || cur->type == REDIR_OUT
				|| cur->type == HERE_DOC || cur->type == DREDIR_OUT))
		{
			cur = cur->next;
			if (cur && cur->type == WHITE_SPACE)
				cur = cur->next;
			if (cur && cur->type == WORD)
				cur = cur->next;
		}
		else if (cur && cur->type == WORD)
			len++;
		if (cur)
			cur = cur->next;
	}
	return (len);
}
