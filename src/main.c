/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:16:01 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/10 19:12:49 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char *av[], char **env)
{
    char *len;
    (void)av;
    (void)env;
    if(ac != 1)
        printf("rak dkhlti ktr mn arg\n");
    len = readline("minishell$ ");
    if (!len)
        return (0);
    // printf("len == %s\n", len);
    return 0;
}
