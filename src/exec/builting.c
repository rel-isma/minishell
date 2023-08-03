#include "../minishell.h"

int		x = 0;

int	ft_exit_builtin(t_list *tmp) // finish fot exit builting
{
	exit((tl(tmp->content))->exit_status);
}

int	ft_echo(t_list *tmp) // echo the exit status
{
	t_list *tm;
	tm = tmp;
	int i = 1;
	int j = 2;

	if (!(tl(tmp->content))->argms[1])
	{
		printf("\n");
		return (1);
	}
	if ((tl(tmp->content))->argms[1][0] == '-'
		&& (tl(tmp->content))->argms[1][1] == 'n')
	{
		while ((tl(tmp->content))->argms[1][i] == 'n')
			i++;
		if ((tl(tmp->content))->argms[1][i] == '\0')
		{
			while ((tl(tmp->content))->argms[j])
			{
				write((tl(tmp->content))->oufile, (tl(tmp->content))->argms[j], ft_strlen((tl(tmp->content))->argms[j]));
				// printf("%s", (tl(tmp->content))->argms[j]);
				if ((tl(tmp->content))->argms[j + 1])
					write((tl(tmp->content))->oufile, " ", 1);
				j++;
			}
		}
		else
		{
			j = 1;
			while ((tl(tmp->content))->argms[j])
			{
				if ((tl(tmp->content))->argms[j + 1])
				{
					printf("%s", (tl(tmp->content))->argms[j]);
					printf(" ");
				}
				else
					printf("%s\n", (tl(tmp->content))->argms[j]);

				j++;
			}
		}
	}
	else
	{
		j = 1;
		while ((tl(tmp->content))->argms[j])
		{
			if ((tl(tmp->content))->argms[j + 1])
			{
				printf("%s", (tl(tmp->content))->argms[j]);
				printf(" ");
			}
			else
				printf("%s\n", (tl(tmp->content))->argms[j]);

			j++;
		}
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
	return (1);
}
int	valid_home(t_list *tmp)
{
	int	home;

	home = 0;
	while ((tl(tmp->content))->envl)
	{
		if (ft_strcmp((tl(tmp->content))->envl->key, "HOME") == 0)
		{
			home++;
			if (chdir((tl(tmp->content))->envl->value))
			{
				printf("cd : no such file or directory: %s\n",
					(tl(tmp->content))->argms[1]);
				return (0);
			}
		}
		(tl(tmp->content))->envl = (tl(tmp->content))->envl->next;
	}
	return (home);
}
void	cd_home(t_list *tmp)
{
	if (valid_home(tmp) == 0)
	{
		printf("HOME not set\n");
	}
}
int	ft_cd(t_list *tmp) // finish
{
	int cd = 0;
	// static int s = 0;
	char current_dir[PATH_MAX];
	char *cd_dir = malloc(sizeof(char) * PATH_MAX);
	if ((tl(tmp->content))->argms[1] == NULL)
	{
		cd = 1;
		cd_home(tmp);
	}
	getcwd(current_dir, sizeof(current_dir));
	cd_dir = ft_strjoin(current_dir, "/");
	cd_dir = ft_strjoin(cd_dir, (tl(tmp->content))->argms[1]);
	if (chdir(cd_dir) && !cd)
	{
		if (getcwd(current_dir, sizeof(current_dir)))
		{
			printf("minishell: cd: %s: Not a directory\n",
				(tl(tmp->content))->argms[1]);
		}
		if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		{
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			chdir("..");
		}
	}
	free(cd_dir);
	return (0);
}

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
/* WEXITSTATUS(exit_status) */
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

int	syntax_unset(char *str)
{
	int	j;

	j = 0;
	if (ft_isdigit(str[0]))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", str);
		return (1);
	}
	while (str[j])
	{
		if (!ft_isalnum(str[j]) && str[j] != '_')
		{
			printf("minishell: unset: `%s': not a valid identifier\n", str);
			return (1);
		}
		j++;
	}
	return (0);
}
int	ft_unset(t_list *tmp) // finish
{
	t_expand *cur;
	t_expand *next;
	t_expand *prev;
	int i = 1;

	next = NULL;
	prev = NULL;

	while ((tl(tmp->content))->argms[i])
	{
		cur = (tl(tmp->content))->envl;
		if (syntax_unset((tl(tmp->content))->argms[i]))
			return (1);
		else
		{
			while (cur)
			{
				if (ft_strcmp(cur->key, (tl(tmp->content))->argms[i]) == 0)
				{
					next = cur->next;
					if (prev)
						prev->next = next;
					else
						(tl(tmp->content))->envl = next;
					free(cur->value);
					free(cur);
				}
				else
					prev = cur;
				if (cur)
					cur = cur->next;
			}
		}
		i++;
	}
	return (0);
}

int	ft_env(t_expand *pp, int *flg)
{
	while ((pp))
	{
		if (ft_strcmp(pp->value, "") == 0 && *flg)
		{
			printf("%s=\n", pp->key);
			pp = pp->next;
		}
		else
		{
			if (pp->key && !(ft_strcmp(pp->value, "") == 0))
				printf("%s", pp->key);
			if (ft_strcmp(pp->value, "") != 0)
				printf("=\"%s\"\n", pp->value);
			pp = pp->next;
		}
	}
	return (0);
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
				printf("declare -x %s", p->key);
			if ((ft_strcmp(p->value, "") == 0 && flg) || ft_strcmp(p->value,
					"") != 0)
				printf("=\"%s\"", p->value);
			printf("\n");
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
				if (exp_e.len2 == 1)
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
				if (!ft_check_duble(exp_e.key, exp_e.vl,
						(tl(tmp->content))->envl, flg))
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

int	ft_builting(t_list *tmp) // not yet
{
	static int flg = 0;

	if (ft_strcmp((tl(tmp->content))->cmd, "echo") == 0)
		return (ft_echo(tmp));
	if (ft_strcmp((tl(tmp->content))->cmd, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp((tl(tmp->content))->cmd, "cd") == 0)
		return (ft_cd(tmp));
	if (ft_strcmp((tl(tmp->content))->cmd, "unset") == 0)
		return (ft_unset(tmp));
	if (ft_strcmp((tl(tmp->content))->cmd, "env") == 0)
		return (ft_env((tl(tmp->content))->envl, &flg));
	if (ft_strcmp((tl(tmp->content))->cmd, "export") == 0)
		return (ft_export(tmp, &flg));
	if (ft_strcmp((tl(tmp->content))->cmd, "exit") == 0)
		return (ft_exit_builtin(tmp));
	// if (ft_strcmp((tl(tmp->content))->cmd, "exit") == 0)
	// {
	// 	if (!(tl(tmp->content))->argms[1])
	// 		ft_exit_builtin(tmp);
	// }
	return 0;
}
// ba9i blan f exit status u ghda nbda l execv;