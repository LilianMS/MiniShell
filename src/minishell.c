#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

int	main(__attribute__((unused)) int argc, \
	__attribute__((unused)) char **argv, char **envp)
{
	t_mini	mini;

	init_minishell(&mini, envp);
	while (1)
	{
		g_signal_status = 0;
		update_mini(&mini);
		mini.line = readline(PINK_BOLD"minishell> "RESET);
		if (m_is_input_null(&mini))
			break ;
		m_minishell_on(&mini);
	}
	m_close_fds(&mini);
	rl_clear_history();
	m_free_env_list(mini.env_list);
	return (mini.exit_status);
}
