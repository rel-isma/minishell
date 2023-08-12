/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_needs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:28 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/11 01:31:39 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_expand *pp, t_list *tmp)
{
	while ((pp))
	{
		if (pp->key && pp->value && ft_strcmp(pp->value, "") == 0)
		{
			write((tl(tmp->content))->oufile, pp->key, ft_strlen(pp->key));
			write((tl(tmp->content))->oufile, "=\n", ft_strlen("=\n"));
		}
		else if (pp->key && pp->value && (ft_strcmp(pp->value, "")))
		{
			if (pp->key && (ft_strcmp(pp->value, "")))
			{
				write((tl(tmp->content))->oufile, pp->key, ft_strlen(pp->key));
				write((tl(tmp->content))->oufile, "=", ft_strlen("="));
			}
			if (ft_strcmp(pp->value, "") != 0)
			{
				write((tl(tmp->content))->oufile, pp->value,
					ft_strlen(pp->value));
				write((tl(tmp->content))->oufile, "\n", ft_strlen("\n"));
			}
		}
		pp = pp->next;
	}
	return (0);
}

int	ft_pwd(void)
{
	char	ptr[PATH_MAX];

	if (getcwd(ptr, sizeof(ptr)))
	{
		printf("%s\n", ptr);
		return (0);
	}
	else
		printf("%s\n", g_minishell.str);
	return (1);
}
