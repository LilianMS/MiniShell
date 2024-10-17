/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rascunhos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:39:16 by lsampiet          #+#    #+#             */
/*   Updated: 2024/10/15 17:41:25 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main() {
    char *line;

    while (1) {
        line = readline("minishell> ");
		if (!line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		add_history(line);
		if (*line) {
            // Quebra o comando em argumentos (simplesmente por espaço aqui)
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
        // Libera a memória alocada pela função readline
        free(line);
    }

    return 0;
}

// Para compilar: gcc -o minishell minishell.c -lreadline