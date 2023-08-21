/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:28 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/21 01:33:49 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_expand *pp, t_list *tmp, int flg)
{
	while ((pp))
	{
		if (pp->key && pp->value && (ft_strcmp(pp->value, "") == 0))
		{
			write(((t_cmd *)(tmp->content))->oufile, pp->key,
				ft_strlen(pp->key));
			if (flg)
				write(((t_cmd *)(tmp->content))->oufile, "=", 1);
			write(((t_cmd *)(tmp->content))->oufile, "\n", 1);
		}
		else if (pp->value && (ft_strcmp(pp->value, "")) != 0)
		{
			if (pp->key)
			{
				write(((t_cmd *)(tmp->content))->oufile, pp->key,
					ft_strlen(pp->key));
				write(((t_cmd *)(tmp->content))->oufile, "=", 1);
				write(((t_cmd *)(tmp->content))->oufile, pp->value,
					ft_strlen(pp->value));
				write(((t_cmd *)(tmp->content))->oufile, "\n", 1);
			}
		}
		pp = pp->next;
	}
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
