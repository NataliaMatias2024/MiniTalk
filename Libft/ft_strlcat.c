/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:23:51 by namatias          #+#    #+#             */
/*   Updated: 2025/07/25 18:24:11 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	s2_size;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	s2_size = j;
	if (n > 0 && n > i)
	{
		j = 0;
		while (j + i < n - 1 && s2[j])
		{
			s1[i + j] = s2[j];
			j++;
		}
		s1[i + j] = '\0';
	}
	if (n <= i)
		return (n + s2_size);
	return (i + s2_size);
}
