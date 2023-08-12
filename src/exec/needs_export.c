/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needs_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:42:25 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/11 16:43:19 by rel-isma         ###   ########.fr       */
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
	j = 0;
	s = ft_substr(str, 0, ft_len_export(str));
	if (s[0] == '=' || ft_isdigit(s[0]))
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		return (free(s), 1);
	}
	while (s[j])
	{
		if ((s[j] == '+' && s[j + 1] == '='))
			flg = 1;
		else if (!ft_isalnum(s[j]) && s[j] != '_' && s[j] != '=' && !flg)
		{
			printf("minishell: export: `%s': not a valid identifier\n", s);
			return (free(s), 1);
		}
		j++;
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
		if (p->key)
		{
			write((tl(tmp->content))->oufile, "declare -x ", 11);
			write((tl(tmp->content))->oufile, p->key, ft_strlen(p->key));
		}
		if (((ft_strcmp(p->value, "") == 0 && flg) || ft_strcmp(p->value,
					"") != 0) && p->value)
		{
			write((tl(tmp->content))->oufile, "=\"", 2);
			write((tl(tmp->content))->oufile, p->value, ft_strlen(p->value));
			write((tl(tmp->content))->oufile, "\"", 1);
		}
		p = p->next;
		write((tl(tmp->content))->oufile, "\n", 1);
	}
}

void	ft_print_export(t_list *tmp, int flg, t_expand *p)
{
	int	i;

	i = 1;
	if ((tl(tmp->content))->argms[i] && g_minishell.err == 1
		&& (ft_strcmp((tl(tmp->content))->argms[i], "") == 0))
	{
		printf("bash: export: `': not a valid identifier\n");
		g_minishell.err = 0;
		g_minishell.exit_code = 1;
	}
	else if ((tl(tmp->content))->argms[i] && g_minishell.www == 2
		&& ft_strcmp((tl(tmp->content))->argms[i], "") == 0)
	{
		while ((tl(tmp->content))->argms[i] && g_minishell.www == 2
			&& ft_strcmp((tl(tmp->content))->argms[i], "") == 0)
			i++;
	}
	if (!(tl(tmp->content))->argms[i])
	{
		sort_list(p);
		ft_print_exp(p, tmp, flg);
	}
}
