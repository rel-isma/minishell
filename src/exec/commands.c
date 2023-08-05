/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:39 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/05 05:11:24 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void    ft_exec_in_child(t_list *cmd, char *path, char **env, int *fd, int  old_fd)
{
    struct stat file_info;
    //dup
    if (ft_check_builting(cmd))
    {
        g_minishell.exit_code = ft_builting(cmd);
        exit(g_minishell.exit_code);
    }
    // dup stdout to pipe
    if (cmd->next)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        close(fd[0]);
    }

    // dup stdout to out redirection
    if ((tl(cmd->content))->oufilename)
    {
        dup2((tl(cmd->content))->oufile, STDOUT_FILENO);
    }
    // dup stdin to pipe
    if (old_fd != -1)
    {
        dup2(old_fd, STDIN_FILENO);
        close(old_fd);
    }
    // dup stdin to in redirection
    if ((tl(cmd->content))->infilename)
    {
        if ((ft_strncmp("/tmp/.heredoc>", (tl(cmd->content))->infilename, 14) == 0))
            (tl(cmd->content))->infile = open((tl(cmd->content))->infilename, O_RDONLY);
        dup2((tl(cmd->content))->infile, STDIN_FILENO);
    }
    // close all open file descriptors in child
    // close_all_fds();
    //
    // execute cmd
    // printf("[%s]\n", path);
    execve(path, (tl(cmd->content))->argms, env);
    if (stat(path, &file_info) == 0)
    {
        printf("minishell: %s: is a directory\n", path);
        exit(126);
    }
    else
    {
        printf("minishell: %s: No such file or directory\n", path);
        exit(127);
    }
}

void    ft_free_tab(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}
void    command_not_found(char *str)
{
    printf("minishell: %s: command not found\n", str);
}
int ft_exec_cmd(t_list *cmd, int *fd, int old_fd)
{
    char    *path;
    char    **env;
    pid_t   pid;
    // int i = 0;

    if ( (tl(cmd->content))->argms[0][0] != '\0' && (tl(cmd->content))->infile != -1)
    {
        if(ft_strcmp((tl(cmd->content))->cmd, "..") == 0)
        {
                command_not_found((tl(cmd->content))->cmd);
                            g_minishell.exit_code = 127;
            return 0;
        }
        path = ft_get_path(cmd);
        env = ft_get_env_tab(cmd);
    
        // in case command not found
        if (path == NULL)
        {
            if((tl(cmd->content))->lvl)
                printf("minishell: %s: No such file or directory\n", (tl(cmd->content))->cmd);
            else 
                command_not_found((tl(cmd->content))->cmd);
            ft_free_tab(env);
            free(path);
            g_minishell.exit_code = 127;
            return 0;
        }
        // fork
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            free(path);
            ft_free_tab(env);
            return -1;
        }
        else if (pid == 0)
            ft_exec_in_child(cmd, path, env, fd, old_fd);
        ft_free_tab(env);
        free(path);
    }
    // in parent
    // wait for last command
    if (!cmd->next)
    {
        waitpid(pid, &g_minishell.exit_code, 0);
        if( WIFEXITED(g_minishell.exit_code))
            (tl(cmd->content))->exit_status = WEXITSTATUS(g_minishell.exit_code);
    }
    //close pipe
    if (cmd->next)
        close(fd[1]);
    if (old_fd != -1)
        close(old_fd);
    return 0;
}

void    ft_commands(t_list *commands)
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
        if (ft_exec_cmd(curr, fd, old_fd) == -1)
            break ;
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
