/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:22:51 by namatias          #+#    #+#             */
/*   Updated: 2025/12/11 12:51:55 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal, siginfo_t *infos_sigaction, void *empty)
{
	static t_signal		config;

	(void) empty;
	//Primeiro vamos guardar o ID do client que esta enviando a mensagem. 
	//Nosso server precisa receber sinais de diferentes clientes SEM misturar os bits recebidos.
	//Se for um cliente novo o campo client_pid estará zerado e entrará no if
	if (config.client_pid != infos_sigaction->si_pid)
	{
		//Resetamos todos os campos para que nao seja pego lixo de memoria da leitura anterior
		config.bits_received = 0;
		config.current_char = 0;
		//Salvamos o pid do nomo CLIENT
		config.client_pid = infos_sigaction->si_pid;
	}
	//Verificamos o sinal que estamos recebendo. SE for 1 iremos utilizar o operador OU de bit
	//assim garantimos q ele seja adicionado sem alterar nenhum outro valor que ja estiver la
	if (signal == SIGUSR1)
		config.current_char |= (1 << config.bits_received);
	//SE o sinal recebido for 0, nós apenas aumentamos o contador pois o zero é preenchido automaticamente
	config.bits_received++;
	//Quando tivermos os 8bits podemos finalmente imprimir o char, e resetar os contadores para o
	//proximo char a ser impresso. 
	if (config.bits_received == 8)
	{
		if (config.current_char == '\0')
			write(1, "\n", 1);
		else
			write(1, &config.current_char, 1);
		config.bits_received = 0;
		config.current_char = 0;
	}
	//Finalmente enviamos um sinal para o client avisando que ja recebemos os 8bits e imprimimos o char
	//que ele pode mandar o proximo.
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
	//serve para zerar todos os valores que estejam na struct, o lixo de memoria. 
	//Equivalente a iniciar uma variavel com valor 0 antes de realemente usa-la no codigo. 
	sigemptyset(&s_sigaction.sa_mask);
	//Ela permite que nosso sigaction recebe 3 parametros ao inves de 1. Basicamente avisa o sistema
	//que queremos usar a versão mais moderna da função.
	s_sigaction.sa_flags = SA_SIGINFO;
	//Ao ativar o modo avançado (SA_SIGINFO) nós somos "obrigados" a usar o modo avançado para lidar com os
	//sinais, por tando chamamos o sigaction, ao inves do handler padrao (só recebe signal)
	s_sigaction.sa_sigaction = signal_handler;
	//Os proximos 2 ifs são uma otimizaçao de linhas. Basicamente eu estou salvando as configurações feitas
	//nas linahs anteriores e verificando se tudo foi definido corretamente.
	//Passamos:
	//1 - Os sinais iremos receber e utilizar no nosso programa (SINAIS ALVO).
	//2 - O endereço da struct com as novas regras (flags) que definimos e nosso HANDLER.
	//3 - NULL, O ultimo campo seria o backup da config antiga da struct, mas como nao vamos utiliza-la 
	//o null indica que o sistema n precisa salvar nada.
	// Caso tenha algum erro nas nossas definições anteriores a config nao é realizada e retorna erro (-1).
	if (sigaction(SIGUSR1, &s_sigaction, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &s_sigaction, NULL) == -1)
		return (1);
	//É oq faz nosso server permanecer aberto e executando até que nós o encerremos ctrl + C
	while (1)
		pause();
	return (0);
}
