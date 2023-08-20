/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:28 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/19 02:49:50 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_expand *pp, t_list *tmp)
{
	while ((pp))
	{
		if (pp->key && pp->value && ft_strcmp(pp->value, "") == 0)
		{
			write(((t_cmd *)(tmp->content))->oufile, pp->key,
				ft_strlen(pp->key));
			write(((t_cmd *)(tmp->content))->oufile, "=\n", ft_strlen("=\n"));
		}
		else if (pp->key && pp->value && (ft_strcmp(pp->value, "")))
		{
			if (pp->key && (ft_strcmp(pp->value, "")))
			{
				write(((t_cmd *)(tmp->content))->oufile, pp->key,
					ft_strlen(pp->key));
				write(((t_cmd *)(tmp->content))->oufile, "=", ft_strlen("="));
			}
			if (ft_strcmp(pp->value, "") != 0)
			{
				write(((t_cmd *)(tmp->content))->oufile, pp->value,
					ft_strlen(pp->value));
				write(((t_cmd *)(tmp->content))->oufile, "\n", ft_strlen("\n"));
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
