/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_argms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:41:16 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/22 20:54:33 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_join_specail(t_lexer **cur, t_parser **new)
{
	int	i;

	i = 0;
	if (*cur && (!check_no_word(*cur)))
	{
		i = (*cur)->type;
		ft_parseradd_back(new, ft_parsernew((*cur)->value, 0, i));
		*cur = (*cur)->next;
	}
}

t_parser	*ft_join_word(t_lexer *cur, int flg)
{
	t_parser	*new;
	char		*str;
	char		*tmp;

	new = NULL;
	while (cur)
	{
		flg = 0;
		str = ft_strdup("");
		while (cur && check_no_word(cur))
		{
			flg = 1;
			if (!*cur->value && cur->type == ENV)
				g_minishell.env = 5;
			tmp = str;
			str = ft_strjoin(str, cur->value);
			free(tmp);
			cur = cur->next;
		}
		if (flg)
			ft_parseradd_back(&new, ft_parsernew(str, 1, WORD));
		ft_join_specail(&cur, &new);
		free(str);
	}
	return (new);
}

char	ft_get_after_here(t_lexer *lst)
{
	while (lst)
	{
		if (lst->type == HERE_DOC)
		{
			lst = lst->next;
			if (lst && lst->type == WHITE_SPACE)
				lst = lst->next;
			if (lst)
				return (lst->value[0]);
		}
		lst = lst->next;
	}
	return ('\0');
}

t_list	*ft_join_argms(t_lexer **lst, t_expand *env)
{
	t_parser	*tok_new;
	t_list		*cmd;
	char		str;
	int			flg;

	flg = 0;
	str = ft_get_after_here(*lst);
	ft_delete_double_quote(lst);
	ft_delete_quote(lst);
	tok_new = ft_join_word(*lst, flg);
	ft_free_lexer(*lst);
	cmd = ft_join_cmd(tok_new, env, str);
	ft_free_list_join(tok_new);
	return (cmd);
}
