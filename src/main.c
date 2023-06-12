/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:16:01 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/12 14:45:55 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int ac, char *av[], char **env)
{
    char *line;
    (void)av;
    (void)env;
    if(ac != 1)
        printf("rak dkhlti ktr mn arg\n");
    line = readline("minishell$ ");
    if (!line)
        return (0);
    ft_lexer(line);
    return 0;
}
