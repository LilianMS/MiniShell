#include "../includes/minishell.h"

// Variável global para armazenar o status do sinal
volatile sig_atomic_t	g_signal_status = 0;

void	m_heredoc_delete_files(t_mini *mini)
{
	char	filename[256];
	char	*suffix;

	mini->hdoc->suffix_doc--;
	while (mini->hdoc->suffix_doc >= 0)
	{
		suffix = ft_itoa(mini->hdoc->suffix_doc);
		strcpy(filename, ".heredoc");
		strcat(filename, suffix);
		free(suffix);
		if (unlink(filename) == 0)
			ft_printf("Deleted %s successfully.\n", filename); // ----- debug
		else
			perror("Error deleting file");
		mini->hdoc->suffix_doc--;
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_mini	mini;

	init_minishell(&mini, envp);
	while (1)
	{
		mini.line = readline("minishell> ");
		if (m_is_input_null(&mini))
			break ;
		m_lexical_analysis(&mini);
		free(mini.line);
	}
	rl_clear_history();
	m_free_env_list(mini.env_list);
	m_heredoc_delete_files(&mini);
	free(mini.hdoc);
	return (0);
}
