<h1 align="center">
    <img alt="minitalk" width="200px" src="https://raw.githubusercontent.com/NataliaMatias2024/42-project-badges/main/badges/minitalke.png">
</h1>

# 💬 Minitalk - @42SP
**Score:** 100/100 ✅ (Sem bônus)

Este repositório contém a implementação do **Minitalk**, um projeto de comunicação entre processos (IPC) do currículo da [42 São Paulo](https://www.42sp.org.br/).
O objetivo é criar um cliente e um servidor que trocam mensagens utilizando apenas os sinais UNIX `SIGUSR1` e `SIGUSR2`.

## 🚀 Objetivos

> - Implementar a comunicação entre dois processos distintos (Cliente e Servidor).
> - Utilizar apenas sinais UNIX para a transmissão de dados.
> - Garantir a integridade da mensagem através de um mecanismo de sincronização (Handshake).
> - Manipular bits individualmente para converter caracteres em sinais e vice-versa.

## 🛠️ Tecnologias e Conceitos
<div align="left">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C" />
  <img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black" alt="Linux" />
</div>

> - **UNIX Signals:** Uso de `SIGUSR1` (representando o bit 1) e `SIGUSR2` (representando o bit 0).
> - **Bitwise Operations:** Deslocamento de bits (`>>`) e máscaras binárias para decompor e reconstruir bytes.
> - **Process Management:** Uso de PIDs para endereçamento e `sigaction` para tratamento avançado de sinais.
> - **Synchronization:** Implementação de um protocolo de confirmação onde o servidor avisa o cliente que está pronto para o próximo bit.

## 📁 Estrutura do Projeto

```bash
.
├── Libft/             # biblioteca reutilizável
├── include/           # Header (minitalk.h) com definições e protótipos
├── src/               # Código-fonte do cliente e do servidor (.c)
├── Makefile           # Automação de compilação (all, clean, fclean, re)
└── README.md          # Este arquivo
```

## ⚙️ Compilação e Uso
### 1. Compilação gera 2 arquivos executáveis: `client` e `server`
```bash
$ make
```

### 2. Primeiro, inicie o servidor para obter o seu PID:
```bash
$ ./server
Process ID (PID): 12345
```

### 3. Em seguida, utilize o cliente para enviar uma mensagem:
```bash
$ ./client 12345 "Olá galerinha de cowboy"
```

##🧠 Lições Aprendidas

**- O Protocolo Handshake:** Sem sincronização o cliente envia bits mais rápido do que o servidor os processa, ocorrendo erros e perda de informação. A solução foi usar um `pause()` no cliente para esperar por um `SIGUSR1` de volta do servidor antes de enviar o próximo bit.

**- Tratamento com sigaction:** Substituí o `signal` clássico pelo `sigaction` com a flag `SA_SIGINFO`. Isso permite que o servidor identifique o PID exato do cliente (`si_pid`) para enviar os sinais de confirmação de volta.

**- Manipulação de Bits:** Reforcei o domínio sobre operadores binários. Entender como percorrer os 8 bits de um `unsigned char`,  decompor e remontá-lo perfeitamente no outro processo foi fundamental para a comunicação funcionar.

**- Variáveis Voláteis:** O uso de `static volatile int` para flags de sinais, garante que o compilador não otimize a variável de forma indesejada, garantindo que o programa sempre perceba a chegada de novos sinais.
