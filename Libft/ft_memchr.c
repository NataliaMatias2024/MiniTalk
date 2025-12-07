/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:34:18 by namatias          #+#    #+#             */
/*   Updated: 2025/07/30 18:35:11 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*array;
	unsigned char		character;
	size_t				i;

	array = (const unsigned char *)s;
	character = c;
	i = 0;
	while (i < n)
	{
		if (array[i] == character)
			return ((void *)(array + i));
		i++;
	}
	return (NULL);
}
