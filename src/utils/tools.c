#include "../../includes/minishell.h"
#include "debug.h" // ----- debug
#include "builtin.h" // ----- debug

void	init_minishell(t_mini *mini, char **envp)
{
	signal(SIGINT, m_sig_int);
	signal(SIGQUIT, SIG_IGN);
	ft_bzero(mini, sizeof(t_mini));
	mini->line = NULL;
	mini->env_list = m_create_env_list(envp);
	mini->tree = NULL;
	// temporario para heredoc
	mini->hdoc = malloc(sizeof(t_hdoc));
	ft_bzero(mini->hdoc, sizeof(t_hdoc));
	mini->hdoc->delimiter = NULL;
	mini->hdoc->temp_fd = 0;
	mini->hdoc->i = 0;
	mini->hdoc->parsed_list = NULL;
	mini->hdoc->env_list = mini->env_list;
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

void	m_lexical_analysis(t_mini *mini)
{
	t_token	*token_list;
	t_token	*parsed_list;

	token_list = NULL;
	parsed_list = NULL;
	if (!m_check_line_input(mini->line))
		return ;
	m_tokenize(&token_list, mini->line);
	if (token_list != NULL)
	{
		if (!m_validate_tokens(&token_list))
		{
			m_free_tokens(&token_list);
			return ;
		}
	}
	m_parse_tokens(&token_list, &parsed_list, mini->env_list);
	list_printer(&parsed_list); // ----- debug
	m_free_tokens(&token_list);
	if(m_get_delimiter_lexeme(parsed_list)) // ---------------- debug // uso em m_execute_commands
		m_heredoc(&parsed_list, *mini); // ----- debug // uso em m_execute_commands
	mini->tree = m_binary_tree(mini->tree, &parsed_list);
	if (m_is_builtin(parsed_list)) // ---------------- debug // uso em m_execute_commands
		m_execute_builtin(mini, parsed_list); // ----- debug // uso em m_execute_commands
	m_tree_cleaner(mini->tree);
	m_free_tokens(&parsed_list);
}
