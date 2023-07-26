/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:23:56 by rel-isma          #+#    #+#             */
/*   Updated: 2023/07/25 23:36:22 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_open_all(t_parser **lst, int *infile, int *oufile, char **env)
{
	if (*lst && ((*lst)->type == REDIR_IN || (*lst)->type == REDIR_OUT
			|| (*lst)->type == HERE_DOC || (*lst)->type == DREDIR_OUT))
	{
		ft_open_redir_out(lst, oufile);
		ft_open_redir_in(lst, infile);
		ft_open_here_doc(lst, infile, env);
		ft_open_dredir_out(lst, oufile);
		// puts((*lst)->value);
	}
}

void	ft_creat_cmd_arg(t_parser **lst, int *infile, int *oufile, char **arg, char **env)
{
	int	i;

	i = 0;
	while ((*lst) && (*lst)->type != PIPE_LINE)
	{
		if ((*lst)->type == WORD)
		{
			arg[i++] = ft_strdup((*lst)->value);
			(*lst) = (*lst)->next;
		}
		if ((*lst) && (*lst)->type == WHITE_SPACE)
			(*lst) = (*lst)->next;
		ft_open_all(lst, infile, oufile, env);
	}
	arg[i] = NULL;
}


t_cmd	*ft_join_cmd(t_parser *lst, char **env)
{
	t_cmd	*new;
	char	**arg;
	int		infile;
	int		oufile;

	new = NULL;
	infile = 0;
	oufile = 1;
	while (lst)
	{
		arg = malloc((ft_len(lst) + 1) * sizeof(char *));
		if (!arg)
			return (NULL);
		ft_creat_cmd_arg(&lst, &infile, &oufile, arg, env);
		if (!*arg)
			ft_cmdadd_back(&new, ft_cmdnew("", arg, infile, oufile));
		else
			ft_cmdadd_back(&new, ft_cmdnew(arg[0], arg, infile, oufile));
		infile = 0;
		oufile = 1;
		if (lst)
			lst = lst->next;
	}
	return (new);
}
