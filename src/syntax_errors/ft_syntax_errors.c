/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:15:02 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/14 00:04:39 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_syntax_errors(t_lexer *token_lst)
{
   t_lexer *current;

   current = token_lst;
   while (current)
   {
        
        current = current->next;   
   }  
}