/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 10:06:47 by namatias          #+#    #+#             */
/*   Updated: 2025/12/07 10:35:13 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_bist_char(int server_pid, char c)
{
    int	i;

	i = 8;
	while (i >= 0)
    {
		if ((c >> i) & 1)
			kill(server_pid, SIGUSR2);  // Envia um bit (0 ou 1)
		else
			kill(server_pid, SIGUSR1); // Envia um bit (0 ou 1)
       i--;
	}
}