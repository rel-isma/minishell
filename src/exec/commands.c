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

void    ft_commands(t_list *commands, t_expand *env)
{
    if (g_minishell.stop_exection)
        return ;
    
    t_list  *curr;
    int     old_fd;
    int     fd[2] = {-1, -1};

    curr = commands;
    while (curr)
    {
        g_minishell.command_executing = 1;
        old_fd = fd[0];
        if (curr->next)
            pipe(fd);
        if (ft_exec_cmd(curr, fd, old_fd))
            return ;
        curr = curr->next;
    }
    while (wait(NULL) != -1)
        ;
    g_minishell.command_executing = 0;
    //close_all_fds(commands);
    /***************************************************************************
     * get exit status using waitpid macros WIFEXITED WEXITSTATUS WIFSIG WTERMSIG
     */
}

void    ft_exec_in_child(t_list *cmd, char *path, char **env, int *fd, int  old_fd)
{
    //dup
    if (ft_check(cmd))
    {
        g_minishell.exit_code = ft_builting(cmd);
        exit(g_minishell.exit_code);
    }
    // dup stdout to pipe
    if (cmd->next)
    {
        dup2(STDOUT_FILENO, fd[1]);
        close(fd[1]);
        close(fd[0]);
    }

    // if (input == 0)
    //     input = fd[0];
    // else 
    //     close
    // if (output == 1)
    //     utput = fd[1];
    // dup stdout to out redirection
    if ((tl(cmd->content))->oufilename)
    {
        dup2(STDOUT_FILENO, (tl(cmd->content))->oufile);
    }
    // dup stdin to pipe
    if (old_fd != -1)
    {
        dup2(STDIN_FILENO, old_fd);
        close(old_fd);
    }
    // dup stdin to in redirection
    if ((tl(cmd->content))->infilename)
    {
        // if ()
        // // handle herdoc
        // else
        dup2(STDOUT_FILENO, (tl(cmd->content))->infile);
    }
    // close all open file descriptors in child
    // close_all_fds();
    //
    // execute cmd
    execve(path, (tl(cmd->content))->argms, env);
    /*************************************************
     * check if is a directory with stat
     * print ("bash: /tmp: is a directory")
     * set ext_code = 126
     * ***********************************************/
    perror(path);
}

char    *ft_get_path(t_list *cmd)
{
    // int check = 0;
    // int i = 0;
    // int r = 0;
    // while((tl(tmp->content))->argms[r])
    //     r++;
    // char **path = get_path((tl(tmp->content))->envl);
    // int status = 0;
    // char *cmd = ft_strjoin("/", (tl(tmp->content))->cmd);
    // // char **argv = malloc(sizeof(char *) * r);
    // // if(!(tl(tmp->content))->argms[1])
    // //     argv[0] = (tl(tmp->content))->argms[0];
    // // else
    // // {
    // //     r = 1;
    // //     while((tl(tmp->content))->argms[1])
    // //         {argv[r] = (tl(tmp->content))->argms[r];
    // //         r++;
    // //         }
    // // // }
    // char *val = NULL;
    // while(path[i])
    // {
    //     if(access(ft_strjoin(path[i], cmd), F_OK) == 0)
    //     {
    //         val = ft_strjoin(path[i], cmd);
    //         check++;
    //         break;
    //     }
    //     i++;
    // }
    // pid_t id = fork();
    // if(id == 0)
    // {
 
    //         if(execve(val, ((tl(tmp->content))->argms), env) == -1)
    //         {
    //             printf("minishell: command not found: %s\n", (tl(tmp->content))->cmd);
    //             exit(1);
    //         }
    // }
    // else 
    //     waitpid(id, NULL, 0);
    // if (WIFEXITED(status)) 
    //     (tl(tmp->content))->exit_status = WEXITSTATUS(status);
}

char    **ft_get_env_tab(t_list *cmd)
{
    int len;
	int 	i;
    t_expand *cur_size;
    char    **env;

    cur_size = (tl(cmd->content))->envl;
	i  = 0;
    while (cur_size)
    {
        len++;
        cur_size = cur_size->next;
    }
    env = malloc(len + 1 * sizeof(char *));
	if (!env)
		return (NULL);
	while ((tl(cmd->content))->envl)
	{
		env[i] = ft_strjoin((tl(cmd->content))->envl->key, (tl(cmd->content))->envl->value);
		(tl(cmd->content))->envl = (tl(cmd->content))->envl->next;
	}
}

int ft_exec_cmd(t_list *cmd, int *fd, int old_fd)
{
    char    *path;
    char    **env;
    pid_t   pid;

    path = ft_get_path(cmd);
    env = ft_get_env_tab(cmd);
    
    // in case command not found
    if (path == NULL)
        return (ft_free_tab(env), command_not_found(), g_minishell.exit_code = 127, 0);

    // fork
    pid = fork();
    if (pid == -1)
        return (free(path), ft_free_tab(env), perror("fork"),1);
    else if (pid == 0)
        ft_exec_in_child(cmd, path, env, fd, old_fd);
    // in parent
    // wait for last command
    if (!cmd->next)
        waitpid(pid, &g_minishell.exit_code, 0);
    //close pipe
    if (cmd->next)
        close(fd[1]);
    if (old_fd != -1)
        close(old_fd);
    return (0);
}
