#include "../minishell.h"
int x = 0;

int        ft_exit_builtin(t_cmd *tmp)//finish fot exit builting
{
        exit(tmp->exit_status);
}
void        ft_echo(t_cmd *tmp) //echo the exit status 
{
    t_cmd *tm;
    tm = tmp;
    int i = 1;
    int j = 2;
    if(tmp->argms[1][0] == '-' && tmp->argms[1][1] == 'n')
    {
        while(tmp->argms[1][i] == 'n')
            i++;
        if(tmp->argms[1][i] == '\0')
        {
            while(tmp->argms[j])
            {
            printf("%s", tmp->argms[j]);
            if(tmp->argms[j + 1])
                printf(" ");
                j++;
            }
        }
        else 
        {
            j = 1;
            while(tmp->argms[j])
            {
            if(tmp->argms[j + 1])
            {printf("%s", tmp->argms[j]);
                printf(" ");
            }
            else 
            printf("%s\n", tmp->argms[j]);
                
            j++;
            }
        }
    }
    else 
    {
        j = 1;
            while(tmp->argms[j])
            {
            if(tmp->argms[j + 1])
            {printf("%s", tmp->argms[j]);
                printf(" ");
            }
            else 
            printf("%s\n", tmp->argms[j]);
                
            j++;
            }
    }
}
void    ft_pwd()//finish
{
    char ptr[PATH_MAX];
    if(getcwd(ptr, sizeof(ptr)))
    {    printf("%s\n", ptr);
    }
    else 
        x = 1;
}
int     valid_home(t_expand *pp, t_cmd *tmp)
{
    int home = 0;
        while(pp)
        {
            if(ft_strcmp(pp->key, "HOME") == 0)
            {
                    home++;
                    if(chdir(pp->value))
                    {
                         printf("cd : no such file or directory: %s\n", tmp->argms[1]);
                        return(0);
                    }
            }
            pp = pp->next;
        }
        return(home);
}
void     cd_home(t_expand *pp,t_cmd *tmp)
{
    if(valid_home( pp, tmp) == 0)
    {
        printf("HOME not set\n");
        x = 1;
    }
}
void    ft_cd(t_cmd *tmp,t_expand *pp)//finish
{
    // static int s = 0;
    char current_dir[PATH_MAX];
    char *cd_dir = malloc(sizeof(char) * PATH_MAX);
    if(tmp->argms[1] == NULL)
    {
        cd_home(pp,tmp);
    }
    getcwd(current_dir, sizeof(current_dir));
    cd_dir = ft_strjoin(current_dir, "/");
    cd_dir = ft_strjoin(cd_dir , tmp->argms[1]);
    if(chdir(cd_dir))
    {
            if(getcwd(current_dir, sizeof(current_dir)))
            {
                printf("cd: %s: Not a directory\n", tmp->argms[1]);
                x = 1;
            }
            if(getcwd(current_dir, sizeof(current_dir)) == NULL)
            {
                printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
                x = 1;
                chdir("..");
            }
    }
    free(cd_dir);
}

/* WEXITSTATUS(exit_status) */
int     syntax(char *str)
{

    int j = 0;
    while(str[j])
    {
        if(ft_isdigit(str[0]))
        {
                printf("bash: unset: `%s': not a valid identifier\n", str);
                return(0);
        }
        else if(!ft_isalnum(str[j]) && !ft_isalnum(str[j]) && str[j] != '_')
                {
                printf("bash: unset: `%s': not a valid identifier\n", str);
                return(0);
                }
        j++;
    }
    return(1);
}
void	ft_unset(t_expand *pp, t_cmd *tmp) //finish
{
	t_expand	*cur;
	t_expand	*next;
	t_expand	*prev;
    int i = 1;

	next = NULL;
	prev = NULL;

    while (tmp->argms[i])
    {
	    cur = pp;
    if(syntax(tmp->argms[i]))
    {
	    while (cur)
	    {
		    if (ft_strcmp(cur->key, tmp->argms[i]) == 0)
		        {
			        next = cur->next;
			        if (prev)
				        prev->next = next;
			        else
				        pp = next;
			        free(cur->value);
			        free(cur);
		}
		else
			prev = cur;
		cur = cur->next;
	    }
    }
    i++;
    }
}
void   ft_env(t_expand *pp) //finish
{
    
    
    while((pp))
    {
        printf("%s=%s\n", pp->key, pp->value);
        pp = pp->next;
    }
}
void        ft_export(t_expand *pp, t_cmd *tmp)
{
    int i = 1;
    t_expand *p;
    p = pp;
    if(!tmp->argms[1])
    {
        sort_list(pp);
        while(pp)
        {
            printf("declare -x %s=%s\n", pp->key, pp->value);
            pp = pp->next;
        }

    }
    else if(tmp->argms[i])
    {
        while(tmp->argms[i])
        {
        if(syntax(tmp->argms[i]))
            {
                //zid dak l arg f export;
            }
        i++;
        }
    }
    pp = p;
}
void       ft_builting(t_cmd *tmp, t_expand *pp)//not yet
{
    if(ft_strcmp(tmp->cmd, "echo") == 0)
        ft_echo(tmp);
    if(ft_strcmp(tmp->cmd, "pwd") == 0)
        ft_pwd();
    if(ft_strcmp(tmp->cmd, "cd") == 0)
        ft_cd(tmp, pp);
    if(ft_strcmp(tmp->cmd, "unset") == 0)
        ft_unset(pp, tmp);
    if(ft_strcmp(tmp->cmd, "env") == 0)
        ft_env(pp);
    if(ft_strcmp(tmp->cmd, "export") == 0)
        ft_export(pp,tmp);
    if(ft_strcmp(tmp->cmd, "exit") == 0)
    {
        if(!tmp->argms[1])
            ft_exit_builtin(tmp);
    }
    
}
//ba9i blan f exit status u ghda nbda l execv;