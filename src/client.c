/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 10:06:47 by namatias          #+#    #+#             */
/*   Updated: 2025/12/11 12:51:06 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// static restringe o escopo da variável, ou seja, apenas o client.c terá acesso
// volatile avisa pro compilador nao otimizar essa variavel!! 
//Assim ele nao acusa que loopings como while (signal_flag == 0) de ser sempre zero
//e tente substituir por while (1), gerando um looping infinito
//Alem disso a função principal da nossa flag ficar salvo em uma variavel global é
//que usamos funções diferentes que utilizam dela para funcionar, e nao podemos
//redefini-la dentro das funções pois isso faria com que o valor nao fosse compartilhado
//Assim o papel da global é avisar ao compilador:
//A variavel signal_flag utilizada nas funções set_signal_flag e signal_sender são as MESMA!
//E estao definidar aqui com essas caracteristicas! 
static volatile int	signal_flag = 0;

static void	set_signal_flag(int signal)
{
	if (signal == SIGUSR1)
		signal_flag = 1;
}

void	signal_sender(pid_t server_pid, unsigned char c)
{
	int	i;
//Nossa função receve o pid do server e um char = 1 byte = 8 bits
//por isso nosso looping será repetido 8 vezes, uma para cada bit
	i = 0;
	while (i < 8)
	{
		//começamos setando a signal_flag para 0, pois nesse momento vamos enviar nossas infos
		signal_flag = 0;
		//Deslocamos o bit da posição i para a direita, isolamos ele com o & e vemos seu valor.
		//SE for igual a 1 enviamos SIGURS1 caso contrario enviamos o SIGURS2
		if (((c >> i) & 1) == 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		i++;
		//Apos cada envio nosso client fica em espera ate receber o sinal 1 de volta do servidor. 
		//Só depois ela envia o proximo bit
		while (signal_flag == 0)
			pause();
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_sigaction;
	pid_t				server_pid;
	int					i;

//Verifico se estamos recebendo o numero de argumentos validos (programa + pid server + mensagem a ser enviada)
	if (argc != 3)
		return (1);
//Para o pid ser recebido no formato correto realizamos um atoi e fazemos um cast para o formato exigido para o envio de sinal (pid_t)
	server_pid = (pid_t)ft_atoi(argv[1]);
//Com o pod salvo, verificamos se foi passado um numero invalido (negativo) OU se o envio de teste kill(pid , 0) retorna erro (-1).
//Assim podemos testar se o pid é valido e se temos autorização para enviar sinais para ele SEM de fato enviar.
	if (server_pid <= 0 || kill(server_pid, 0) == -1)
		return (1);
//Essa função server para limpar as configurações pré existentes/ lixos de memoria. Evitando comportamentos inesperados
	sigemptyset(&s_sigaction.sa_mask);
//Avisamos que vamos usar o modo padrão/mais simpes de envio de sinal
	s_sigaction.sa_flags = 0;
//Informamos como iremos reagir ao sinal do servidor, ou seja, quando receber um aviso do servidor chamaremos direto a função set_signal_flag
//Ela nos avisará que podemos enviar o proximo char
	s_sigaction.sa_handler = set_signal_flag;
//Realizamos o cadastro das configurações estabelecidas, informando que receberemos o SIGUSR1 do server e acionaremos a funçao set_signal_flag
	if (sigaction(SIGUSR1, &s_sigaction, NULL) == -1)
		return (1);
//Após as configurações iniciais, começamos o envio da mensagem de fato!
//O argv[2] é a mensagem inteira, por isso repetiremos o looping até a ultima posição
	i = 0;
	while (argv[2][i])
	{
		//para cada i enviado, ou seja, para cada caracter enviado utilizaremos a função signal_sender
		//ela que transformará o char em bits e enviará bit a bit para nosso server. 
		signal_sender(server_pid, (unsigned char)argv[2][i]);
		i++;
	}
	//como nosso looping se encerra antes de enviar o operador de fim de string, enviamos ele separadamente fora do looping
	signal_sender(server_pid, '\0');
	return (0);
}
