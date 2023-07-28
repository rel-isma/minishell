#include "../minishell.h"

int		x = 0;

int	ft_exit_builtin(t_list *tmp) // finish fot exit builting
{
	exit((tl(tmp->content))->exit_status);
}
void	ft_echo(t_list *tmp) // echo the exit status
{
	t_list *tm;
	tm = tmp;
	int i = 1;
	int j = 2;
	if ((tl(tmp->content))->argms[1][0] == '-'
		&& (tl(tmp->content))->argms[1][1] == 'n')
	{
		while ((tl(tmp->content))->argms[1][i] == 'n')
			i++;
		if ((tl(tmp->content))->argms[1][i] == '\0')
		{
			while ((tl(tmp->content))->argms[j])
			{
				printf("%s", (tl(tmp->content))->argms[j]);
				if ((tl(tmp->content))->argms[j + 1])
					printf(" ");
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
}
void	ft_pwd(void) // finish
{
	char ptr[PATH_MAX];
	if (getcwd(ptr, sizeof(ptr)))
	{
		printf("%s\n", ptr);
	}
	else
		x = 1;
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
		x = 1;
	}
}
void	ft_cd(t_list *tmp) // finish
{
	// static int s = 0;
	char current_dir[PATH_MAX];
	char *cd_dir = malloc(sizeof(char) * PATH_MAX);
	if ((tl(tmp->content))->argms[1] == NULL)
	{
		cd_home(tmp);
	}
	getcwd(current_dir, sizeof(current_dir));
	cd_dir = ft_strjoin(current_dir, "/");
	cd_dir = ft_strjoin(cd_dir, (tl(tmp->content))->argms[1]);
	if (chdir(cd_dir))
	{
		if (getcwd(current_dir, sizeof(current_dir)))
		{
			printf("cd: %s: Not a directory\n", (tl(tmp->content))->argms[1]);
			x = 1;
		}
		if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		{
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			x = 1;
			chdir("..");
		}
	}
	free(cd_dir);
}

/* WEXITSTATUS(exit_status) */
int	syntax(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (ft_isdigit(str[0]))
		{
			printf("bash: unset: `%s': not a valid identifier\n", str);
			return (0);
		}
		else if (!ft_isalnum(str[j]) && !ft_isalnum(str[j]) && str[j] != '_')
		{
			printf("bash: unset: `%s': not a valid identifier\n", str);
			return (0);
		}
		j++;
	}
	return (1);
}
void	ft_unset(t_list *tmp) // finish
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
		if (syntax((tl(tmp->content))->argms[i]))
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
}
void	ft_env(t_expand *pp) // finish
{
	while ((pp))
	{
		printf("%s=%s\n", pp->key, pp->value);
		pp = pp->next;
	}
}

void	ft_export(t_list *tmp)
{
	int			i;
	t_expand	*p;

	i = 1;
	p = (tl(tmp->content))->envl;
	if (!(tl(tmp->content))->argms[1])
	{
		sort_list(p);
		while (p)
		{
			printf("declare -x %s=%s\n", p->key, p->value);
			p = p->next;
		}
	}
	else if ((tl(tmp->content))->argms[i])
	{
		while ((tl(tmp->content))->argms[i])
		{
			if (syntax((tl(tmp->content))->argms[i]))
			{
				// zid dak l arg f export;
			}
			i++;
		}
	}
}

void	ft_builting(t_list *tmp) // not yet
{
	if (ft_strcmp((tl(tmp->content))->cmd, "echo") == 0)
		ft_echo(tmp);
	if (ft_strcmp((tl(tmp->content))->cmd, "pwd") == 0)
		ft_pwd();
	if (ft_strcmp((tl(tmp->content))->cmd, "cd") == 0)
		ft_cd(tmp);
	if (ft_strcmp((tl(tmp->content))->cmd, "unset") == 0)
		ft_unset(tmp);
	if (ft_strcmp((tl(tmp->content))->cmd, "env") == 0)
		ft_env((tl(tmp->content))->envl);
	if (ft_strcmp((tl(tmp->content))->cmd, "export") == 0)
		ft_export(tmp);
	if (ft_strcmp((tl(tmp->content))->cmd, "exit") == 0)
	{
		if (!(tl(tmp->content))->argms[1])
			ft_exit_builtin(tmp);
	}
}
// ba9i blan f exit status u ghda nbda l execv;