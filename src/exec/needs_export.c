/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needs_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:42:25 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/21 20:14:30 by yoel-bas         ###   ########.fr       */
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
	s = ft_substr(str, 0, ft_len_export(str) + 1);
	if (s[0] == '=' || ft_isdigit(s[0]))
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		g_minishell.exit_code = 1;
		return (free(s), 1);
	}
	while (s[++j])
	{
		if ((s[j] == '+' && s[j + 1] == '='))
			flg = 1;
		else if (!ft_isalnum(s[j]) && s[j] != '_' && s[j] != '=' && !flg)
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			g_minishell.exit_code = 1;
			return (free(s), 1);
		}
	}
	return (free(s), 0);
}

int	ft_check_duble(char *key, char *vl, t_expand *env, int flg)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (ft_strcmp(env->value, vl) != 0 || ft_strcmp(env->value,
					vl) == 0)
			{
				if (flg)
				{
					env->value = ft_strjoin(env->value, vl);
					return (1);
				}
				else
				{
					free(env->value);
					env->value = ft_strdup(vl);
					return (1);
				}
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
		if (p->key && p->flg)
		{
			write(((t_cmd *)(tmp->content))->oufile, "declare -x ", 11);
			write(((t_cmd *)(tmp->content))->oufile, p->key, ft_strlen(p->key));
		}
		if (((ft_strcmp(p->value, "") == 0 && flg) || ft_strcmp(p->value,
					"") != 0) && p->value && p->flg)
		{
			write(((t_cmd *)(tmp->content))->oufile, "=\"", 2);
			write(((t_cmd *)(tmp->content))->oufile, p->value,
				ft_strlen(p->value));
			write(((t_cmd *)(tmp->content))->oufile, "\"", 1);
		}
		if (p->key && p->flg)
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
		printf("bash: export: `': not a valid identifier\n");
		g_minishell.err = 0;
		g_minishell.exit_code = 1;
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
		ft_print_exp(cur, tmp, flg);
		free_list(cur);
	}
}
