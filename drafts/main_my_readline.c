#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libs/libft/include/libft.h"
#include <string.h>

typedef struct s_history
{
    char            *command;
    struct s_history *next;
}               t_history;

t_history *add_history(t_history *history, char *command);
void display_history(t_history *history);
char *read_line(void);  // Sua função para ler a linha do terminal

int main(void)
{
    char        *input;
    t_history   *history = NULL;

    while (1)
    {
        // Exibe o prompt
        write(STDOUT_FILENO, "my_shell$ ", 10);

        // Lê a linha de comando
        input = read_line();
        if (!input)
            break;

        // Se o input for EOF (Ctrl-D), sair do shell
        if (input[0] == '\0')
        {
            free(input);
            break;
        }

        // Verifica se o comando é "history" e exibe o histórico
        if (strcmp(input, "history") == 0)
            display_history(history);
        else
        {
            // Adiciona o comando ao histórico
            history = add_history(history, input);

            // Aqui você pode adicionar a lógica para executar o comando digitado
            // Por enquanto, apenas exibimos o comando digitado
            write(STDOUT_FILENO, input, ft_strlen(input));
            write(STDOUT_FILENO, "\n", 1);
        }

        free(input);
    }

    return (0);
}
