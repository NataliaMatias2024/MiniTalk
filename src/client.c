/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 10:06:47 by namatias          #+#    #+#             */
/*   Updated: 2025/12/10 17:55:20 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
** Global variable used to synchronize the client with the server.
** It is updated inside the signal handler when an signal is received.
** the client only sends the next bit after the server's confirmation.
*/
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
		signal_flag = 0;
		if (((c >> i) & 1) == 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
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
		return (1);
	server_pid = (pid_t)ft_atoi(argv[1]);
	if (server_pid <= 0 || kill(server_pid, 0) == -1)
		return (1);
	sigemptyset(&s_sigaction.sa_mask);
	s_sigaction.sa_flags = 0;
	s_sigaction.sa_handler = set_signal_flag;
	if (sigaction(SIGUSR1, &s_sigaction, NULL) == -1)
		return (1);
	i = 0;
	while (argv[2][i])
	{
		signal_sender(server_pid, (unsigned char)argv[2][i]);
		i++;
	}
	signal_sender(server_pid, '\0');
	return (0);
}
