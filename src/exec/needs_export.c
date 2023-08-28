/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needs_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:42:25 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/28 03:40:25 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_len_export(char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '=')
		{
			len++;
			return (len);
		}
		len++;
	}
	return (len);
}

int	syntax_export(char *str)
{
	int		j;
	int		flg;
	char	*s;

	flg = 0;
	j = -1;
	s = ft_substr(str, 0, ft_len_export(str));
	if (s[0] == '+' || s[0] == '=' || ft_isdigit(s[0]))
	{
		printf_msg(str, " export : ");
		return (free(s), g_minishell.exit_code = 1, 1);
	}
	while (s[++j])
	{
		if ((s[j] == '+' && s[j + 1] == '='))
			flg = 1;
		else if (!ft_isalnum(s[j]) && s[j] != '_' && s[j] != '=' && !flg)
		{
			printf_msg(str, " export : ");
			return (free(s), g_minishell.exit_code = 1, 1);
		}
	}
	return (free(s), 0);
}

int	ft_check_duble(char *key, char *vl, t_expand *env, int flg)
{
	char	*str;

	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if ((ft_strcmp(env->value, vl) != 0 || ft_strcmp(env->value,
						vl) == 0) && ft_strcmp(vl, "") != 0)
			{
				if (flg)
				{
					str = env->value;
					env->value = ft_strjoin(env->value, vl);
					return (free(str), 1);
				}
				else
					return (free(env->value), env->value = ft_strdup(vl), 1);
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	ft_print_exp(t_expand *p, t_list *tmp, int flg)
{
	while (p)
	{
		if (p->key && ft_strcmp(p->key, "") != 0)
		{
			write(((t_cmd *)(tmp->content))->oufile, "declare -x ", 11);
			write(((t_cmd *)(tmp->content))->oufile, p->key, ft_strlen(p->key));
		}
		if (((ft_strcmp(p->value, "") == 0 && flg) || ft_strcmp(p->value,
					"") != 0) && p->value)
		{
			write(((t_cmd *)(tmp->content))->oufile, "=\"", 2);
			write(((t_cmd *)(tmp->content))->oufile, p->value,
				ft_strlen(p->value));
			write(((t_cmd *)(tmp->content))->oufile, "\"", 1);
		}
		if (p->key && ft_strcmp(p->key, "") != 0)
			write(((t_cmd *)(tmp->content))->oufile, "\n", 1);
		p = p->next;
	}
}

void	ft_print_export(t_list *tmp, int flg, t_expand *p)
{
	int			i;
	t_expand	*cur;

	i = 1;
	if (((t_cmd *)(tmp->content))->argms[i] && g_minishell.err == 1
		&& (ft_strcmp(((t_cmd *)(tmp->content))->argms[i], "") == 0))
	{
		ft_putstr_fd("bash: export: `': not a valid identifier\n", 2);
		g_minishell.err = 0;
		g_minishell.exit_code = 1;
		return ;
	}
	else if (((t_cmd *)(tmp->content))->argms[i] && g_minishell.www == 2
		&& ft_strcmp(((t_cmd *)(tmp->content))->argms[i], "") == 0)
	{
		while (((t_cmd *)(tmp->content))->argms[i] && g_minishell.www == 2
			&& ft_strcmp(((t_cmd *)(tmp->content))->argms[i], "") == 0)
			i++;
	}
	if (!((t_cmd *)(tmp->content))->argms[i])
	{
		cur = copy_list(p);
		sort_list(cur);
		return (ft_print_exp(cur, tmp, flg), free_list(cur));
	}
}
