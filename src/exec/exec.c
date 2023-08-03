#include "../minishell.h"

int     ft_check_builting(t_list *tmp)
{
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
void    ft_exec(t_list *tmp)
{
    if (ft_check_builting(tmp)  /* and only one command*/)
    {
        // int old_stdout = -1;
        // // int old_stdin = -1;

        // if ((tl(tmp->content))->oufilename)
        // {
        //     printf(">>out %s:\n", (tl(tmp->content))->oufilename);
        //     old_stdout = dup(STDOUT_FILENO);
        //     dup2((tl(tmp->content))->oufile, STDOUT_FILENO);
        //     close((tl(tmp->content))->oufile);
        // }
        if ((tl(tmp->content))->infile != -1)
            ft_builting(tmp);
        // if (old_stdout != -1)
        // {
        //     dup2(old_stdout, STDOUT_FILENO);
        //     close (old_stdout);
        // }
    }
    else
        ft_commands(tmp);
}
