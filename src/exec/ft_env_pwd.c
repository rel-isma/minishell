/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:28 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/23 16:24:20 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_list *tmp, t_expand *pp)
{
	if (ft_strcmp(pp->key, "_") == 0)
	{
		write(((t_cmd *)(tmp->content))->oufile, pp->key, ft_strlen(pp->key));
		write(((t_cmd *)(tmp->content))->oufile, "=", 1);
		ft_putstr_fd("/Users/yoel-bas/Desktop/minishell/./minishell/env",
			((t_cmd *)(tmp->content))->oufile);
		write(((t_cmd *)(tmp->content))->oufile, "\n", 1);
	}
	else
	{
		write(((t_cmd *)(tmp->content))->oufile, pp->key, ft_strlen(pp->key));
		write(((t_cmd *)(tmp->content))->oufile, "=", 1);
		write(((t_cmd *)(tmp->content))->oufile, pp->value,
			ft_strlen(pp->value));
		write(((t_cmd *)(tmp->content))->oufile, "\n", 1);
	}
}

void	ft_env(t_expand *pp, t_list *tmp, int flg)
{
	while ((pp))
	{
		if (pp->key && pp->value && (ft_strcmp(pp->value, "") == 0))
		{
			if (flg)
			{
				write(((t_cmd *)(tmp->content))->oufile, pp->key,
					ft_strlen(pp->key));
				write(((t_cmd *)(tmp->content))->oufile, "=", 1);
				write(((t_cmd *)(tmp->content))->oufile, "\n", 1);
			}
		}
		else if (pp->value && (ft_strcmp(pp->value, "")) != 0)
		{
			if (pp->key)
				print_env(tmp, pp);
		}
		pp = pp->next;
	}
}

int	ft_pwd(t_list *tmp)
{
	char	ptr[PATH_MAX];

	if (getcwd(ptr, sizeof(ptr)))
	{
		ft_putstr_fd(ptr, ((t_cmd *)(tmp->content))->oufile);
		write(((t_cmd *)(tmp->content))->oufile, "\n", 1);
		return (0);
	}
	else
	{
		ft_putstr_fd(g_minishell.str, ((t_cmd *)(tmp->content))->oufile);
		write(((t_cmd *)(tmp->content))->oufile, "\n", 1);
	}
	return (1);
}
