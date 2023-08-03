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
        // if ()
        // // handle herdoc
        // else
        dup2((tl(cmd->content))->infile, STDOUT_FILENO);
    }
    // close all open file descriptors in child
    // close_all_fds();
    //
    // execute cmd
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

char    *ft_getenv(char *path, t_expand *env)
{
    char *str;

    while (env)
    {
        if (ft_strcmp(path, env->key) == 0)
        {
            str = env->value;
            return (str);
        }
        env = env->next;
    }
    return NULL;
}
char    *ft_get_path(t_list *cmd)
{
    char       **paths;
    char        *path;
    char        *cmd_path;
    char        *cmd_path1;
    int         i;
    char *cmd_str = (tl(cmd->content))->cmd;

    i = 0;
    if (cmd_str[0] == '/' || (ft_strnstr(cmd_str, "/", ft_strlen(cmd_str))))
        return cmd_str;
    paths = ft_split(ft_getenv("PATH", (tl(cmd->content))->envl), ':');
    if (!paths)
        return NULL;
    while (paths[i])
    {
        cmd_path1 = ft_strjoin(paths[i], "/");
        cmd_path = ft_strjoin(cmd_path1, (tl(cmd->content))->cmd);
        if (access(cmd_path, F_OK | X_OK) == 0)
        {
            free(cmd_path1);
            path = cmd_path;
            ft_free_tab(paths);
            return (path);
        }
        i++;
        free(cmd_path);
        free(cmd_path1);
    }
    ft_free_tab(paths);
    return NULL;
}

char    **ft_get_env_tab(t_list *cmd)
{
    int len  = 0;
	int 	i = 0;;
    t_expand *cur_size;
    char    **env;
    char *str;

    cur_size = (tl(cmd->content))->envl;
    while (cur_size)
    {
        len++;
        cur_size = cur_size->next;
    }
    env = malloc((len + 1) * sizeof(char *));
	if (!env)
		return (NULL);
    cur_size = (tl(cmd->content))->envl;
	while (cur_size)
	{
        str = ft_strjoin(cur_size->key, "=");
		env[i] = ft_strjoin(str, cur_size->value);
		cur_size = cur_size->next;
        i++;
        free(str);
	}
    env[i] = NULL;
    return (env);
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

    path = ft_get_path(cmd);
    env = ft_get_env_tab(cmd);
   
    // in case command not found
    if (path == NULL)
    {
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
    // in parent
    // wait for last command
    if (!cmd->next)
        waitpid(pid, &g_minishell.exit_code, 0);
    //close pipe
    if (cmd->next)
        close(fd[1]);
    if (old_fd != -1)
        close(old_fd);
    ft_free_tab(env);
    free(path);
    return 0;
}
