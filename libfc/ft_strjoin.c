/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-isma <rel-isma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:39:00 by rel-isma          #+#    #+#             */
/*   Updated: 2023/08/19 01:04:36 by rel-isma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*pcat;
	char		*cat_str;

	if (!s1 || !s2)
		return (NULL);
	cat_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!cat_str)
		return (NULL);
	pcat = cat_str;
	while (*s1)
		*pcat++ = *s1++;
	while (*s2)
		*pcat++ = *s2++;
	*pcat = '\0';
	return (cat_str);
}
