/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:39 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/18 23:16:56 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void    ft_exec_in_child(t_list *cmd, char *path, char **env, int *fd, int  old_fd)
{
    struct stat file_info;
    //dup
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
    if (ft_check_builting(cmd))
    {
        g_minishell.exit_code = ft_builting(cmd);
        exit(g_minishell.exit_code);
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
        // g_minishell.exit_code = 1;
        exit(126);
    }
    else
    {
        write(STDERR_FILENO, "minishell: ", 11);
        write(STDERR_FILENO, path, ft_strlen(path));
        perror(" ");
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

    if((tl(cmd->content))->cmd[0] == '\0' && (tl(cmd->content))->type != 0 && (tl(cmd->content))->type != WHITE_SPACE && g_minishell.env != 5 )
    {
        command_not_found((tl(cmd->content))->cmd);
        g_minishell.exit_code = 127;
        return 0;
    }

    if ((tl(cmd->content))->argms[0] && (tl(cmd->content))->argms[0][0] != '\0' && (tl(cmd->content))->infile != -1)
    {
        if(ft_strcmp((tl(cmd->content))->cmd, "..") == 0 || ft_strcmp((tl(cmd->content))->cmd, ".") == 0 )
        {
                command_not_found((tl(cmd->content))->cmd);
                            g_minishell.exit_code = 127;
            return 0;
        }
        path = ft_get_path(cmd);
        env = ft_get_env_tab(cmd);
        if (path == NULL)
        {
                command_not_found((tl(cmd->content))->cmd);
            ft_free_tab(env);
            free(path);
            g_minishell.exit_code = 127;
            return 0;
        }
      
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

    if (!cmd->next)
    {
        waitpid(pid, &g_minishell.exit_code, 0);
        if( WIFEXITED(g_minishell.exit_code))
        {
            g_minishell.exit_code = WEXITSTATUS(g_minishell.exit_code);
            
        }
        else if (WTERMSIG(g_minishell.exit_code))
        {
            g_minishell.exit_code = 128 + WTERMSIG(g_minishell.exit_code);
            if (WTERMSIG(g_minishell.exit_code) == 2)
                write(1, "\n", 1);
            else if (WTERMSIG(g_minishell.exit_code) == 3)
                write(1, "Quit: 3\n", 8);
         else if(g_minishell.exit_code == 11)
            ft_putstr_fd("Segmentation fault : 11\n", 2);
        else if(g_minishell.exit_code == 10)
            ft_putstr_fd("bus error : 10\n", 2);
        }
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
}
