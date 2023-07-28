/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs_exp2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 00:06:27 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/26 22:41:49 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	idx;

	idx = 0;
	while ((s1[idx] == s2[idx]) && (s1[idx] != '\0' && s2[idx] != '\0'))
		idx++;
	return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
}

void	ft_expand_valid(t_expand *cur, t_lexer *tmp, int flg)
{
	while (cur)
	{
			if (tmp && flg == 0 && tmp->type == ENV
				&& ft_strcmp(cur->key, (tmp->value + 1)) == 0)
			{
				free(tmp->value);
				tmp->value = ft_strdup(cur->value);
				break ;
			}
			if (tmp && flg && tmp->type == ENV && tmp->status != IN_QUOTE
				&& ft_strcmp(cur->key, (tmp->value + 1)) == 0)
			{
				free(tmp->value);
				tmp->value = ft_strdup(cur->value);
				break ;
			}
		cur = cur->next;
	}
}

void	ft_expand_no_valid(t_lexer *tmp, char *str)
{
	if (tmp && tmp->type == ENV && tmp->status != IN_QUOTE
		&& ft_strcmp(tmp->value, str) == 0)
	{
		if (ft_strcmp(tmp->value, "$") == 0 && tmp->status == GENERAL)
			tmp->value = ft_strdup("");
		else if (ft_strcmp(tmp->value, "$") == 0)
			tmp->value = ft_strdup("$");
		else if (ft_strcmp(tmp->value, "$?") == 0)
			tmp->value = ft_strdup("$?");
		else
			tmp->value = ft_strdup("");
	}
	free(str);
}

void	ft_check_after_here_doc(t_lexer **tmp)
{
	if ((*tmp)->type == HERE_DOC && (*tmp)->status != IN_DQUOTE)
	{
		*tmp = (*tmp)->next;
		if (*tmp && (*tmp)->type == WHITE_SPACE)
			*tmp = (*tmp)->next;
		while (*tmp && (*tmp)->type != WHITE_SPACE && ((*tmp)->type == WORD
				|| (*tmp)->type == DOUBLE_QUOTE || (*tmp)->type == QOUTE
				|| (*tmp)->type == ENV))
			*tmp = (*tmp)->next;
	}
}
