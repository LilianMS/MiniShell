// estudos e anotações sobre o status de execução de um programa em C
#include "../../includes/minishell.h"

void	m_update_exit_status(int status)
{
	if (WIFEXITED(status)) // Processo terminou normalmente
		g_signal_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status)) // Processo foi interrompido por sinal
		g_signal_status = 128 + WTERMSIG(status);
}

int	execute_command(char *cmd, char **args, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, args, env); // Executar comando
		perror("execve"); // Apenas é executado se execve falhar
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0); // Esperar processo filho terminar
		m_update_exit_status(status);
	}
	else
	{
		perror("fork");
		g_signal_status = 1; // Erro ao criar processo filho
	}
	return (g_signal_status);
}
