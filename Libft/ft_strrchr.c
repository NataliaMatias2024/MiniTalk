/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:09:51 by namatias          #+#    #+#             */
/*   Updated: 2025/07/27 15:10:06 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	aux;

	i = 0;
	aux = -1;
	while (1)
	{
		if (s[i] == (char)c)
			aux = i;
		if (s[i] == '\0')
			break ;
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	else if (aux != -1)
		return ((char *)&s[aux]);
	return (NULL);
}
