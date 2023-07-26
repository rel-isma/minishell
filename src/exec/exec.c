#include "../minishell.h"
int     ft_check(t_cmd *tmp)
{
    
    if(ft_strcmp(tmp->cmd, "echo") == 0)
        return(1);
    else if(ft_strcmp(tmp->cmd, "cd") == 0)
        return(1);
    else if(ft_strcmp(tmp->cmd, "pwd") == 0)
        return(1);
    else if(ft_strcmp(tmp->cmd, "export") == 0)
        return(1);
    else if(ft_strcmp(tmp->cmd, "unset") == 0)
        return(1);
    else if(ft_strcmp(tmp->cmd, "exit") == 0)
        return(1);
    else if(ft_strcmp(tmp->cmd, "env") == 0)
        return(1);
    return(0);
}
void    ft_exec(t_cmd *tmp, t_expand *pp)
{
    if(ft_check(tmp))
        ft_builting(tmp, pp);
}