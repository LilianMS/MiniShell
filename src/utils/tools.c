#include "../../includes/minishell.h"
#include "debug.h" // ----- debug
#include "builtin.h" // ----- debug

void	init_minishell(t_mini *mini, char **envp)
{
	ft_bzero(mini, sizeof(t_mini));
	mini->line = NULL;
	mini->env_list = m_create_env_list(envp);
	mini->tree = NULL;
}

void	m_sig_int(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*m_get_delimiter_lexeme(t_token *parsed_list)
{
	t_token	*current;

	current = parsed_list;
	while (current)
	{
		if (current->type == DELIMITER)
			return (current->lexeme);
		current = current->next;
	}
	return (NULL);
}

t_token	*m_lexical_analysis(t_mini *mini)
{
	t_token	* token_list;
	t_token	*parsed_list;

	token_list = NULL;
	parsed_list = NULL;
	if (!m_check_line_input(mini->line))
		return (NULL);
	m_tokenize(&token_list, mini->line);
	if (token_list != NULL)
	{
		if (!m_validate_tokens(token_list))
		{
			m_free_tokens(&token_list);
			return (NULL);
		}
	}
	m_parse_tokens(&token_list, &parsed_list, mini->env_list);
	m_free_tokens(&token_list);
	return (parsed_list);
}
