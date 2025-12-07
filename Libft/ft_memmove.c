/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:04:35 by namatias          #+#    #+#             */
/*   Updated: 2025/08/06 13:23:48 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t					i;
	unsigned char			*chardest;
	const unsigned char		*charsrc;

	if (dest == NULL && src == NULL)
		return (NULL);
	chardest = (unsigned char *)dest;
	charsrc = (const unsigned char *)src;
	if (chardest > charsrc)
	{
		i = n;
		while (i > 0)
		{
			chardest[i - 1] = charsrc[i - 1];
			i--;
		}
	}
	else
	{
		ft_memcpy(chardest, charsrc, n);
	}
	return (dest);
}
