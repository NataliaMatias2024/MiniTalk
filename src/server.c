/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:22:51 by namatias          #+#    #+#             */
/*   Updated: 2025/12/07 10:35:01 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void signal_handler(int signum)
{
   
    if (g_bit_count == 8)
    {
        printf("%c", g_char);//TODO: imprimir o char recebido ate agora
    }
}
int main(void)
{
    struct sigaction sa;
    
    sa.sa_handler = signal_handler; //TODO
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    
    while (1)
        pause();      
    return 0;
}