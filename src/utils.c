/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 10:09:26 by namatias          #+#    #+#             */
/*   Updated: 2025/12/09 13:12:18 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


void	count(int argc)
{
	printf("%d\n", argc);
}

void	teste_make(char *str)
{
	printf("%s\n", str);
}

void	signal_handler(int signal, siginfo_t *infos_sigaction, void *empty)
{
	t_signal		config;

	(void) empty; //apenas para n dar warning de variavel nao utilizada
	config.bits_received = 0; //Setamos ambos para zero pois vamos receber a proxima info,
	config.current_char = 0; //assim q imprimir a atual
	if (signal == SIGUSR1)
		config.current_char |= (1 << config.bits_received);   //TODO : estudar bit wise
	config.bits_received++;

	if (config.bits_received == 8)
	{
		if (config.current_char == '\0')
			write(1, "\n", 1);
		else
			write(1, &config.current_char, 1);
	}
	if (infos_sigaction && infos_sigaction->si_pid > 0)
		kill(infos_sigaction->si_pid, SIGUSR2);
}


	//  /* kill().  */
	// struct
	//   {
	//     __pid_t si_pid;	/* Sending process ID.  */
	//     __uid_t si_uid;	/* Real user ID of sending process.  */
	//   } _kill;
