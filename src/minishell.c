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

void	m_init_signals(void)
{
	signal(SIGINT, m_sig_int);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

static void	update_mini(t_mini *mini)
{
	m_init_signals();
	dup2(mini->backup_fd_in, STDIN_FILENO);
	tcsetattr(STDIN_FILENO, TCSANOW, &mini->term);
	m_exec_signals(1);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_mini	mini;

	init_minishell(&mini, envp);
	while (1)
	{
		g_signal_status = 0;
		update_mini(&mini);
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

//notas
/*
if (!m_check_line_input(mini->line))
		return ;
	m_tokenize(&mini->token_list, mini->line);
	if (mini->token_list != NULL)
	{
		if (!m_validate_tokens(&mini->token_list))
		{
			m_free_tokens(&mini->token_list);
			return ;
		}
	}
	mini->parsed_list = m_parse_tokens(&mini->token_list, &mini->parsed_list, mini->env_list);
	if (m_heredoc_get_delimiter(mini->parsed_list))
		m_heredoc(&mini->parsed_list, mini);
*/