/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:18:02 by rel-isma          #+#    #+#             */
/*   Updated: 2023/06/11 19:52:36 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

typedef enum s_tokenstatus
{
    GENERAL = 1,
    IN_D_C,
	IN_C,
	IN_DOLAR,
}	 t_tokenstatus;

typedef enum s_tokentype
{
    WORD = 1,
    PIPE,
	REDIRECTION,
}	t_tokentype;

typedef struct s_lexer
{
	int				type;
	char			*value;
	struct s_lexer	*next;
}       			t_lexer;

#endif
