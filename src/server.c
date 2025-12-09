/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:22:51 by namatias          #+#    #+#             */
/*   Updated: 2025/12/09 16:36:55 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal, siginfo_t *infos_sigaction, void *empty)
{
	static t_signal		config;

	(void) empty; //apenas para n dar warning de variavel nao utilizada

	if (signal == SIGUSR1)
		config.current_char |= (1 << config.bits_received);   //TODO : estudar bit wise
	config.bits_received++;

	if (config.bits_received == 8)
	{
		if (config.current_char == '\0')
			write(1, "\n", 1);
		else
			write(1, &config.current_char, 1);

	//Resetar para o proximos 8bits
		config.bits_received = 0;
		config.current_char = 0;
	}
	//Confirma recebimento, SIGUSR1 de volta para dizer "Ok, recebi o bit"
	if (infos_sigaction && infos_sigaction->si_pid > 0)
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

	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);

	while (1)
		pause();
	return (0);
}
