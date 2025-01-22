#include "../includes/minishell.h"

// Variável global para armazenar o status do sinal
volatile sig_atomic_t	g_signal_status = 0;

int	m_minishell_on(t_mini *mini)
{
	t_token	*parsed_list;

	parsed_list = m_lexical_analysis(mini);
	if (!parsed_list)
		return (1);
	mini->tree = m_binary_tree(mini->tree, &parsed_list);
	mini->exit_status = m_execution(mini->tree, mini);
	ft_putnbr_fd(mini->exit_status, STDERR_FILENO); // debug
	ft_putendl_fd("", STDERR_FILENO);
	m_tree_cleaner(mini->tree);
	return (mini->exit_status);
}

void	m_init_signals(void)
{
	signal(SIGINT, m_sig_int);
	signal(SIGQUIT, SIG_IGN); // enquanto roda o minishell iginora os sinais de interrupção
	signal(SIGPIPE, SIG_IGN);
}

static void	update_mini(t_mini *mini)
{
	m_init_signals();
	dup2(mini->backup_fd_in, STDIN_FILENO); //
	tcsetattr(STDIN_FILENO, TCSANOW, &mini->term);
	m_exec_signals(1);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_mini	mini;
	// int		status;

	init_minishell(&mini, envp);
	while (1)
	{
		g_signal_status = 0;
		update_mini(&mini);
		mini.line = readline("minishell> ");
		if (m_is_input_null(&mini))
			break ;
		m_minishell_on(&mini);
	}
	rl_clear_history();
	m_free_env_list(mini.env_list);
	return (0);
}
