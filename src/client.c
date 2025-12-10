/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 10:06:47 by namatias          #+#    #+#             */
/*   Updated: 2025/12/10 09:29:06 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile int	signal_flag = 0;

static void	set_signal_flag(int signal)
{
	if (signal == SIGUSR1)
 		signal_flag = 1;
}

void	signal_sender(pid_t server_pid, unsigned char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		//mantem sinal bloqueado
		signal_flag = 0;
		if (((c >> i) & 1) == 1)
			kill(server_pid, SIGUSR1); //manda 1
		else
			kill(server_pid, SIGUSR2); // manda 0
		i++;

		while (signal_flag == 0)
			pause();
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_sigaction;
	pid_t				server_pid;
	int					i;

	if (argc != 3)
	{
		write(1, "Error, insert the correct format. 3 arguments\n", 46);
		return (1);
	}

	server_pid = (pid_t)ft_atoi(argv[1]);
	if (server_pid == 0 || kill(server_pid, 0) == -1)
	{
		write(1, "Error, server pid invalid or signal error\n", 42);
		return (1);
	}

	sigemptyset(&s_sigaction.sa_mask);
	s_sigaction.sa_handler = set_signal_flag;
	s_sigaction.sa_flags = 0;
	sigaction(SIGUSR1, &s_sigaction, NULL); //Servidor vai manda um "ok"

	i = 0;
	while (argv[2][i])
	{
		signal_sender(server_pid, (unsigned char)argv[2][i]);
		i++;
	}
   //envia apenas o nulo no final da string
	signal_sender(server_pid, '\0');
	return (0);
}
