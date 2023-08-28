/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:38:52 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/27 19:06:22 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*help;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		help = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = help;
	}
}
