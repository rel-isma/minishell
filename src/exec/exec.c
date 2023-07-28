#include "../minishell.h"

int     ft_check(t_list *tmp)
{
    printf("[[%s]]\n", (tl(tmp->content))->cmd);
    if(ft_strcmp((tl(tmp->content))->cmd, "echo") == 0)
        return(1);
    else if(ft_strcmp((tl(tmp->content))->cmd, "cd") == 0)
        return(1);
    else if(ft_strcmp((tl(tmp->content))->cmd, "pwd") == 0)
        return(1);
    else if(ft_strcmp((tl(tmp->content))->cmd, "export") == 0)
        return(1);
    else if(ft_strcmp((tl(tmp->content))->cmd, "unset") == 0)
        return(1);
    else if(ft_strcmp((tl(tmp->content))->cmd, "exit") == 0)
        return(1);
    else if(ft_strcmp((tl(tmp->content))->cmd, "env") == 0)
        return(1);
    return(0);
}
void    ft_exec(t_list *tmp, char **env)
{
    if(ft_check(tmp))
        ft_builting(tmp);
    else 
        ft_commands(tmp, env);
}