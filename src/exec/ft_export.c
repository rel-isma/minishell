/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:51:42 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/10 03:46:57 by yoel-bas         ###   ########.fr       */
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
	if (ft_isdigit(s[0]))
	{
		printf("minishell: export: `%s': not a valid identifier\n", s);
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
		while (p)
		{
			if (p->key)
			{
				write((tl(tmp->content))->oufile, "declare -x ", ft_strlen("declare -x "));
				write((tl(tmp->content))->oufile, p->key, ft_strlen(p->key));
			}
			if (((ft_strcmp(p->value, "") == 0 && flg) || ft_strcmp(p->value, "") != 0) && p->value)
			{

				write((tl(tmp->content))->oufile,  "=\"" ,2);
				write((tl(tmp->content))->oufile,  p->value, ft_strlen(p->value));
				write((tl(tmp->content))->oufile,  "\"" ,1);
			write((tl(tmp->content))->oufile,  "\n", 1);
			}
			p = p->next;
		}
	}
}

int	ft_export(t_list *tmp, int *flg1) // not finsh
{
	int i;
	t_expand *p;
	int flg = 0;
	t_exp exp_e;
	

	i = 1;
	p = (tl(tmp->content))->envl;
	ft_print_export(tmp, *flg1, p);
	if ((tl(tmp->content))->argms[i])
	{
		while ((tl(tmp->content))->argms[i])
		{
			if (syntax_export((tl(tmp->content))->argms[i]))
				return (1);
			else
			{
				exp_e.len1 = ft_strlen_env_aftr((tl(tmp->content))->argms[i],
					&flg);
				exp_e.key = ft_substr((tl(tmp->content))->argms[i], 0,
					exp_e.len1);
				exp_e.len2 = ft_strlen_env_befor((tl(tmp->content))->argms[i]);
				if (exp_e.len2 == 1 && (tl(tmp->content))->argms[i][exp_e.len1 + 1] == '\0')
				{
					*flg1 = 1;
					exp_e.vl = ft_strdup("");
				}
				else
				{
					if (flg)
						exp_e.len1 += 1;
					exp_e.vl = ft_substr((tl(tmp->content))->argms[i],
						exp_e.len1 + 1, exp_e.len2);
				}
				if (!ft_check_duble(exp_e.key, exp_e.vl, (tl(tmp->content))->envl, flg))
					ft_lexeradd_back_expnd(&(tl(tmp->content))->envl,
						ft_lexernew_expnd(exp_e.key, exp_e.vl));
				free(exp_e.key);
				free(exp_e.vl);
			}
			i++;
		}
	}
	return (0);
}

