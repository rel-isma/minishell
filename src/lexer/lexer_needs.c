/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_needs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:44:06 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/12 15:59:48 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_lexerlast(t_lexer *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_lexer	*ft_lexernew(char *content, t_status status, t_type type)
{
	t_lexer	*node;

	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->type = type;
	node->status = status;
	node->value = ft_strdup(content);
	node->next = NULL;
	return (node);
}

void	ft_lexeradd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*new_last;

	if (!new)
		return ;
	if (!lst)
    {
        *lst = new;
		return ;
    }
	if (*lst)
	{
		new_last = ft_lexerlast(*lst);
		new_last->next = new;
		return ;
	}
	*lst = new;
}
