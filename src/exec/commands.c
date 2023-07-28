#include "../minishell.h"

char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
char**    get_path(t_expand *pp)
{
    while(pp)
    {
        if(ft_strcmp(pp->key, "PATH") == 0)
        {
            char **str = ft_split(pp->value, ':');
            return(str);
        }
        pp = pp->next;
    }
    return(NULL);
}
void             ft_commands(t_list *tmp, char **env)
{
    int check = 0;
    int i = 0;
    char **path = get_path((tl(tmp->content))->envl);
    int status = 0;
    char *cmd = ft_strjoin("/", (tl(tmp->content))->cmd);
    char *const argv[] = {(tl(tmp->content))->cmd, (tl(tmp->content))->argms[1], NULL};
    char *val = NULL;
    while(path[i])
    {
        if(access(ft_strjoin(path[i], cmd), F_OK) == 0)
        {
            val = ft_strjoin(path[i], cmd);
            check++;
            break;
        }
        i++;
    }
    pid_t id = fork();
    if(id == 0)
    {
        if(execve(val, argv, env) == -1)
        {
            printf("minishell: command not found: %s\n", (tl(tmp->content))->cmd);
            exit(1);
        }
    }
    else 
        waitpid(id, NULL, 0);
    if (WIFEXITED(status)) 
        (tl(tmp->content))->exit_status = WEXITSTATUS(status);
    
}
