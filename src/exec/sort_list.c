/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:49 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/23 02:42:08 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_expand *head)
{
	t_expand	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

t_expand	*copy_list(t_expand *head)
{
	t_expand	*new_head;
	t_expand	*current;

	new_head = NULL;
	current = head;
	while (current != NULL)
	{
		ft_l_back_expnd(&new_head, ft_lexernew_expnd(current->key,
				current->value));
		current = current->next;
	}
	return (new_head);
}

void	swap(t_expand *a, t_expand *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	sort_list(t_expand *head)
{
	int			swapped;
	t_expand	*ptr1;
	t_expand	*lptr;

	lptr = NULL;
	if (head == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}
