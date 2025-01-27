#include "../../includes/minishell.h"

void	init_minishell(t_mini *mini, char **envp)
{
	ft_bzero(mini, sizeof(t_mini));
	mini->line = NULL;
	mini->env_list = m_create_env_list(envp);
	mini->tree = NULL;
	mini->backup_fd_in = dup(STDIN_FILENO);
	tcgetattr(STDIN_FILENO, &mini->term);
	mini->hdoc = malloc(sizeof(t_hdoc));
	ft_bzero(mini->hdoc, sizeof(t_hdoc));
	mini->hdoc->temp_fd = 0;
	mini->hdoc->suffix_doc = -1;
	mini->hdoc->filename = NULL;
}

void	m_sig_int(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_status = 128 + signum;
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
int	m_find_heredoc(t_token *parsed_list)
{
	t_token	*current;

	current = parsed_list;
	while (current)
	{
		if (current->type == REDIR_HEREDOC)
			return (1);
		current = current->next;
	}
	return (0);
}

t_token	*m_lexical_analysis(t_mini *mini)
{
	t_token	*token_list;
	t_token	*parsed_list;

	token_list = NULL;
	parsed_list = NULL;
	if (!m_check_line_input(mini->line))
		return (NULL);
	m_tokenize(&token_list, mini->line);
	if (token_list != NULL)
	{
		if (!m_validate_tokens(&token_list))
		{
			m_free_tokens(&token_list);
			return (NULL);
		}
	}
	m_parse_tokens(&token_list, &parsed_list, mini);
	m_free_tokens(&token_list);
	if (m_find_heredoc(parsed_list))
	{
		if (m_heredoc(&parsed_list, mini) == -1)
		{
			mini->exit_status = 1;
			m_free_tokens(&parsed_list);
			// return (mini->exit_status);
		}
		if (g_signal_status == 130)
		{
			mini->exit_status = 130;
			g_signal_status = 0;
			m_free_tokens(&parsed_list);
			// return (mini->exit_status);
		}
	}
	return (parsed_list);
}
