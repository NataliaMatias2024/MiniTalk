/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:25:28 by namatias          #+#    #+#             */
/*   Updated: 2025/08/06 09:14:58 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_size(int n)
{
	size_t	size;
	long	number;

	number = n;
	size = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		number = number * -1;
		size++;
	}
	while (number > 0)
	{
		number = number / 10;
		size++;
	}
	return (size);
}

static char	*ft_convert(size_t i, long number, char *ptr)
{
	ptr[i] = '\0';
	while (number > 0)
	{
		--i;
		ptr[i] = (number % 10) + '0';
		number = number / 10;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	long		number;

	ptr = malloc ((ft_count_size(n) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	number = n;
	if (number == 0)
	{
		ptr[0] = '0';
		ptr[1] = '\0';
		return (ptr);
	}
	if (number < 0)
	{
		ptr[0] = '-';
		number = number * -1;
	}
	return (ft_convert(ft_count_size(n), number, ptr));
}
