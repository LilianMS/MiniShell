#include "../includes/minishell.h"

// Variável global para armazenar o status do sinal
volatile sig_atomic_t	g_signal_status = 0;

int	m_minishell_on(t_mini *mini)
{
	int		exit_status;
	t_token	*parsed_list;

	exit_status = 0;
	parsed_list = m_lexical_analysis(mini);
	if (!parsed_list)
		return (1);
	mini->tree = m_binary_tree(mini->tree, &parsed_list);
	exit_status = m_execution(mini->tree, mini);
	ft_putnbr_fd(mini->exit_status, STDERR_FILENO);
	ft_putendl_fd("", STDERR_FILENO);
	return (exit_status);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_mini	mini;
	int		status;

	// g_signal_status = 11;
	init_minishell(&mini, envp);
	while (1)
	{
		signal(SIGINT, m_sig_int);
		mini.line = readline("minishell> ");
		if (m_is_input_null(&mini))
			break ;
		if (!*mini.line)
			continue ;
		status = m_minishell_on(&mini); //---> Organizei para centralizar os processos de tokenização, parser e execução dentro dessa nova função
		// free(mini.line);
		m_tree_cleaner(mini.tree);
	}
	rl_clear_history();
	m_free_env_list(mini.env_list);
	return (0);
}
