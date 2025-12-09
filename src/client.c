/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 10:06:47 by namatias          #+#    #+#             */
/*   Updated: 2025/12/09 16:40:10 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// static volatile sig_atomic_t	signal_flag = 0;
// static void	set_signal_flag(int sig);

void	signal_sender(pid_t server_pid, unsigned char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (((c >> i) & 1) == 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		// while (!signal_flag)
		// {
		// 	pause();
		// }
		usleep(500);
		i++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_sigaction;
	pid_t				server_pid;
	int					i;

	if (argc != 3)
		write(1, "Error, insert the correct format. 3 arguments\n", 46);

	server_pid = (pid_t)ft_atoi(argv[1]);
	if (server_pid == 0 || kill(server_pid, 0) == -1)
		write(1, "Error, server pid invalid or signal error\n", 42);

	sigemptyset(&s_sigaction.sa_mask);
	//s_sigaction.sa_sigaction = (void*)signal_flag;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, NULL);

	i = 0;
	while (1)
	{
		signal_sender(server_pid, (unsigned char)argv[2][i]);
		if (argv[2][i] == '\0')
			break ;
		i++;
	}
}

// static void	set_signal_flag(int sig)
// {
// 	(void) sig;
// 	signal_flag = 1;
// }