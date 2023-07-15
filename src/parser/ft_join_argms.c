/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_argms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:41:16 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/15 23:18:55 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_join_specail(t_lexer **cur, t_parser **new, char **str)
{
	int	i;

	i = 0;
	if (*cur && (!check_no_word(*cur)))
	{
		i = (*cur)->type;
		free(*str);
		*str = ft_strdup("");
		ft_parseradd_back(new, ft_parsernew((*cur)->value, 0, i));
		*cur = (*cur)->next;
	}
}

t_parser	*ft_join_cmd(t_lexer *cur)
{
	t_parser	*new;
	char		*str;
	char		*tmp;
	int			flg;

	flg = 1;
	new = NULL;
	str = ft_strdup("");
	while (cur)
	{
		while (cur && check_no_word(cur))
		{
			if (!*cur->value)
				flg = 0;
			tmp = str;
			str = ft_strjoin(str, cur->value);
			free(tmp);
			cur = cur->next;
		}
		ft_parseradd_back(&new, ft_parsernew(str, flg, 1));
		ft_join_specail(&cur, &new, &str);
	}
	return (free(str), new);
}

t_parser	*ft_join_argms(t_lexer **lst)
{
	t_parser	*tok_new;

	ft_delete_double_quote(lst);
	ft_delete_quote(lst);
	tok_new = ft_join_cmd(*lst);
	return (tok_new);
}
