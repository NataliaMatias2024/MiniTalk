/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:22:22 by namatias          #+#    #+#             */
/*   Updated: 2025/12/10 17:58:21 by namatias         ###   ########.fr       */
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
	int				client_pid;
	int				bits_received;
}					t_signal;

#endif