/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:10:19 by namatias          #+#    #+#             */
/*   Updated: 2025/08/01 20:31:13 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *s);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	int		i;
	int		f;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	while (s1[i] && ft_strchr((char *)set, s1[i]))
		i++;
	f = ft_strlen(s1) - 1;
	while (f > i && ft_strchr((char *)set, s1[f]))
		f--;
	if (i > f)
		return (ft_strdup(""));
	strtrim = ft_substr(s1, i, (f - i + 1));
	return (strtrim);
}
