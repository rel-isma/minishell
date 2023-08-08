/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:43:44 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/08/08 05:44:23 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    t_list *tp;
    tp = tmp;
    int i = 1;
    while((tl(tp->content))->argms[i])
    {
        if(ft_strcmp((tl(tp->content))->argms[i], "$?") == 0)
            (tl(tp->content))->argms[i] = ft_itoa(g_minishell.exit_code);
        i++;
    }
    if (ft_check_builting(tmp)  && !(tl(tmp->next)))
    {
        if ((tl(tmp->content))->infile != -1)
            ft_builting(tmp);
    }
    else
        ft_commands(tmp);
}
