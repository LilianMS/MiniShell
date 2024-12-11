#include "../includes/minishell.h"

// Variável global para armazenar o status do sinal
volatile sig_atomic_t	g_signal_status = 0;

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_mini	mini;

	// g_signal_status = 11;
	init_minishell(&mini, envp);
	while (1)
	{
		signal(SIGINT, m_sig_int);
		mini.line = readline("minishell> ");
		if (m_is_input_null(&mini))
			break ;
		m_lexical_analysis(&mini);
		free(mini.line);
	}
	rl_clear_history();
	m_free_env_list(mini.env_list);
	return (0);
}
