#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

int	m_minishell_on(t_mini *mini)
{
	t_token	*parsed_list;

	if (g_signal_status == 130)
	{
		mini->exit_status = 130;
		g_signal_status = 0;
	}
	parsed_list = m_lexical_analysis(mini);
	if (!parsed_list)
	{
		if (g_signal_status == 130)
			mini->exit_status = 130;
		else
			mini->exit_status = 1;
		return (mini->exit_status);
	}
	mini->tree = m_binary_tree(mini->tree, &parsed_list);
	mini->exit_status = m_execution(mini->tree, mini);
	m_tree_cleaner(mini->tree);
	return (mini->exit_status);
}

void	m_heredoc_delete_files(t_mini *mini)
{
	char	filename[256];
	char	*suffix;

	mini->hdoc->suffix_doc--;
	while (mini->hdoc->suffix_doc >= 0)
	{
		suffix = ft_itoa(mini->hdoc->suffix_doc);
		strcpy(filename, "heredoc");
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

void	m_close_fds(t_mini *mini)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	close(mini->backup_fd_in);
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
		m_minishell_on(&mini);
	}
	m_close_fds(&mini);
	rl_clear_history();
	m_free_env_list(mini.env_list);
	return (mini.exit_status);
}
