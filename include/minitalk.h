/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:22:22 by namatias          #+#    #+#             */
/*   Updated: 2025/12/07 11:06:15 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _DEFAULT_SOURCE

# include <unistd.h>
# include <signal.h>
# include "../Libft/libft.h"

typedef struct sigaction
{
	char	c;
	int		bits;
}			t_sigaction;

void	teste_make(char *str);
void	count(int argc);

#endif