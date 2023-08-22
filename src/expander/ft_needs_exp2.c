/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs_exp2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 00:06:27 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/22 03:00:33 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	idx;

	idx = 0;
	if (!s1 || !s2)
		return (1);
	while ((s1[idx] != '\0' && s2[idx] != '\0') && (s1[idx] == s2[idx]))
		idx++;
	return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
}

void	ft_expand_valid(t_expand *cur, t_lexer *tmp, int flg)
{
	while (cur)
	{
		if (tmp && flg == 0 && tmp->type == ENV && ft_strcmp(cur->key,
				(tmp->value + 1)) == 0)
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
	char	*env_;

	if (tmp && tmp->type == ENV && tmp->status != IN_QUOTE
		&& ft_strcmp(tmp->value, str) == 0)
	{
		if (ft_strcmp(tmp->value, "$") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup("$");
		}
		else if (ft_strcmp(tmp->value, "$?") == 0)
		{
			env_ = ft_itoa(g_minishell.exit_code);
			free(tmp->value);
			tmp->value = ft_strdup(env_);
			free(env_);
		}
		else
		{
			g_minishell.www = 2;
			free(tmp->value);
			tmp->value = ft_strdup("");
		}
	}
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
