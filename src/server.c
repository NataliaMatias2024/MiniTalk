/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:22:51 by namatias          #+#    #+#             */
/*   Updated: 2025/12/09 13:13:41 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(void)
{
	struct sigaction	s_sigaction;
	pid_t				pid;

	pid = getpid();

	write(1, "Process ID (PID): ", 18);
	ft_putnbr(pid);
	write(1, "\n", 1);

	sigemptyset(&s_sigaction.sa_mask);
	s_sigaction.sa_sigaction = signal_handler; //TODO: Fazer como o sinal sera tratado. 
	s_sigaction.sa_flags = SA_SIGINFO;
	
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);

	while (1)
		pause();
	return (0);
}
