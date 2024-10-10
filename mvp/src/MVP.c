/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MVP.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:39:16 by lsampiet          #+#    #+#             */
/*   Updated: 2024/10/10 14:08:00 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main() {
	char    *line;

	while (1) {
		line = readline("minishell> ");
		if (!line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		add_history(line);
		if (*line) {
			
			char *args[] = {line, NULL};
			
			// Cria um processo filho para executar o comando
			pid_t pid = fork();
			if (pid == 0) {
				// Processo filho: executa o comando
				if (execve(args[0], args, NULL) == -1) {
					perror("minishell");
				}
				exit(EXIT_FAILURE);
			} else if (pid > 0) {
				// Processo pai: espera o processo filho terminar
				wait(NULL);
			} else {
				perror("fork");
			}
		}
		free(line);
	}

	return 0;
}

// a readline inicia o prompt "minishell> " e lê a linha de comando.
// Se CTRL+D for pressionado, o programa exibirá "exit" e sairá do loop.
// Se a linha de comando não for vazia, ela é adicionada ao histórico de comandos.
// A linha de comando é quebrada em argumentos (simplesmente por espaço aqui).