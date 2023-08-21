/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:17:46 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/21 17:23:57 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*ft_parsernew(char *content, int flg, t_type type)
{
	t_parser	*node;

	if (!*content && !flg)
		return (NULL);
	node = (t_parser *)malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup(content);
	node->next = NULL;
	return (node);
}

void	ft_parseradd_back(t_parser **lst, t_parser *new)
{
	t_parser	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->next = NULL;
}

int	check_no_word(t_lexer *lst)
{
	if ((lst->type == WHITE_SPACE && (lst->status == IN_DQUOTE
				|| lst->status == IN_QUOTE)) || (lst->type == PIPE_LINE
			&& (lst->status == IN_DQUOTE || lst->status == IN_QUOTE))
		|| (lst->type == HERE_DOC && (lst->status == IN_DQUOTE
				|| lst->status == IN_QUOTE)) || (lst->type == DREDIR_OUT
			&& (lst->status == IN_DQUOTE || lst->status == IN_QUOTE))
		|| (lst->type == REDIR_IN && (lst->status == IN_DQUOTE
				|| lst->status == IN_QUOTE)) || (lst->type == REDIR_OUT
			&& (lst->status == IN_DQUOTE || lst->status == IN_QUOTE))
		|| ((lst->type != WHITE_SPACE) && lst->type != PIPE_LINE
			&& lst->type != REDIR_IN && lst->type != REDIR_OUT
			&& lst->type != HERE_DOC && lst->type != DREDIR_OUT))
		return (1);
	else
		return (0);
}

void	ft_free_list_join(t_parser *list)
{
	int			i;
	t_parser	*tmp;

	while (list)
	{
		i = 0;
		tmp = list->next;
		free(list->value);
		free(list);
		list = tmp;
	}
}
