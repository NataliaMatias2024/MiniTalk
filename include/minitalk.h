/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:22:22 by namatias          #+#    #+#             */
/*   Updated: 2025/12/09 13:15:01 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _DEFAULT_SOURCE
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include "../Libft/libft.h"

typedef struct s_signal
{
	unsigned char	current_char;
	int				bits_received;
}					t_signal;

void	signal_handler(int signal, siginfo_t *infos_sigaction, void *empty);
void	teste_make(char *str);
void	count(int argc);

// sighandler_t signal(int signum, sighandler_t handler);
// ->int sigemptyset(sigset_t *set);
// int sigaddset(sigset_t *set, int signum);
// ->int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
// int kill(pid_t pid, int sig);
// ->pid_t getpid(void);
// ->int pause(void);
// unsigned int sleep(unsigned int seconds);
// int usleep(useconds_t usec);
// void exit(int status);


#endif