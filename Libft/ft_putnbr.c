/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:18:22 by namatias          #+#    #+#             */
/*   Updated: 2025/12/09 13:34:23 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	int	min;

	if (nb == 0)
	{
		ft_putchar ('0');
		return ;
	}
	if (nb < 0)
	{
		ft_putchar ('-');
		min = -2147483648;
		if (nb == min)
		{
			write (1, "2147483648", 10);
			return ;
		}
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr (nb / 10);
	}
	ft_putchar ((nb % 10) + '0');
}
