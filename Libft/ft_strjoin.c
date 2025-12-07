/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:43:59 by namatias          #+#    #+#             */
/*   Updated: 2025/08/01 18:43:06 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	protect(char const *s1, char const *s2)
{
	int		size_s1;
	int		size_s2;
	int		size;

	if (!s1)
		size_s1 = 0;
	else
		size_s1 = ft_strlen(s1);
	if (!s2)
		size_s2 = 0;
	else
		size_s2 = ft_strlen(s2);
	size = size_s1 + size_s2;
	return (size);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	str = malloc ((protect(s1, s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
			str[j++] = s1[i++];
	i = 0;
	if (s2)
		while (s2[i])
			str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}
