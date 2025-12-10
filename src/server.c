/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:22:51 by namatias          #+#    #+#             */
/*   Updated: 2025/12/10 18:05:49 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal, siginfo_t *infos_sigaction, void *empty)
{
	static t_signal		config;

	(void) empty;
	if (config.client_pid != infos_sigaction->si_pid)
	{
		config.bits_received = 0;
		config.current_char = 0;
		config.client_pid = infos_sigaction->si_pid;
	}
	if (signal == SIGUSR1)
		config.current_char |= (1 << config.bits_received);
	config.bits_received++;
	if (config.bits_received == 8)
	{
		if (config.current_char == '\0')
			write(1, "\n", 1);
		else
			write(1, &config.current_char, 1);
		config.bits_received = 0;
		config.current_char = 0;
	}
	if (infos_sigaction->si_pid > 0)
		kill(infos_sigaction->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	s_sigaction;
	pid_t				pid;

	pid = getpid();
	write(1, "Process ID (PID): ", 18);
	ft_putnbr(pid);
	write(1, "\n", 1);
	sigemptyset(&s_sigaction.sa_mask);
	s_sigaction.sa_sigaction = signal_handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &s_sigaction, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &s_sigaction, NULL) == -1)
		return (1);
	while (1)
		pause();
	return (0);
}
