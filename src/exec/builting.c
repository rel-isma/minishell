#include "../minishell.h"
void        ft_echo(t_cmd *tmp)
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
void    ft_pwd()
{
    char ptr[PATH_MAX];
    getcwd(ptr, sizeof(ptr));
    printf("%s\n", ptr);
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
        printf("HOME not set\n");
}
void    ft_cd(t_cmd *tmp,t_expand *pp)
{
    static int s = 0;
    char current_dir[PATH_MAX];
    char *cd_dir = malloc(sizeof(char) * PATH_MAX);
    if(tmp->argms[1] == NULL)
        cd_home(pp,tmp);
    getcwd(current_dir, sizeof(current_dir));
    cd_dir = ft_strjoin(current_dir, "/");
    cd_dir = ft_strjoin(cd_dir , tmp->argms[1]);
    if(chdir(cd_dir))
    {
        if(s == 0)
        {
            printf("getcwd fail\n");
            s++;
        }
        else
        {
            while(chdir(cd_dir))
            cd_dir = ft_strjoin(cd_dir, "/..");
            if(chdir(cd_dir) == 0)
                return;
        }
    }
}
void	ft_unset(t_expand *pp, t_cmd *tmp)
{
	t_expand	*cur;
	t_expand	*next;
	t_expand	*prev;

	cur = pp;
	next = NULL;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, tmp->argms[1]) == 0)
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
void   ft_env(t_expand *pp)
{
    
    
    while((pp))
    {
        printf("%s=%s\n", pp->key, pp->value);
        pp = pp->next;
    }
}
void       ft_builting(t_cmd *tmp, t_expand *pp)
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
}