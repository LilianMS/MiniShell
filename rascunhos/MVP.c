/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MVP.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:39:16 by lsampiet          #+#    #+#             */
/*   Updated: 2024/10/04 17:08:43 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h> //adicionar a flag -lreadline ao comando de compilação.
#include <readline/history.h>
#include <sys/types.h> // tipo pid_t
#include <sys/wait.h>

int main() {
    char *line;

    while (1) {
        // Exibe o prompt e lê a linha de comando
        line = readline("minishell> ");
        
        // Adiciona a linha ao histórico de comandos
        add_history(line);
        
        // Verifica se o comando não é vazio
        if (line && *line) {
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