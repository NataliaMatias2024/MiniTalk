/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 10:25:22 by namatias          #+#    #+#             */
/*   Updated: 2025/12/07 10:18:10 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char separator)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != separator && (s[i + 1] == separator || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static int	ft_lenght_words(char const *s, char separator)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != separator)
		i++;
	return (i);
}

static char	**ft_free(char **ptr, int p)
{
	while (p >= 0)
	{
		free(ptr[p]);
		p--;
	}
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, char separator)
{
	size_t	i;
	size_t	j;
	char	**ptr;

	ptr = malloc ((ft_count_words(s, separator) + 1) * sizeof(char *));
	if (!ptr || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != separator)
		{
			ptr[j] = ft_substr(s, i, ft_lenght_words(&s[i], separator));
			if (!ptr[j])
				return (ft_free(ptr, j));
			j++;
			i = i + ft_lenght_words(&s[i], separator);
		}
		else
			i++;
	}
	ptr[j] = NULL;
	return (ptr);
}
