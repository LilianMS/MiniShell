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
		{
			ft_printf("DELIMITER: %s\n", current->lexeme); // ----- debug
			if (current->quote == 0)
				ft_printf("expandir in heredoc: %s\n", current->lexeme); // ----- debug
			else
				ft_printf("não expandir in heredoc: %s\n", current->lexeme); // ----- debug
			return (current->lexeme);
		}
		current = current->next;
	}
	return (NULL);
}

void	m_lexical_analysis(t_mini *mini)
{
	t_token	* token_list;
	t_token	*parsed_list;

	token_list = NULL;
	parsed_list = NULL;
	if (!m_check_line_input(mini->line))
		return ;
	m_tokenize(&token_list, mini->line);
	if (token_list != NULL)
	{
		if (!m_validate_tokens(token_list))
		{
			m_free_tokens(&token_list);
			return ;
		}
	}
	m_parse_tokens(&token_list, &parsed_list, mini->env_list);
	list_printer(&parsed_list); // ----- debug
	m_free_tokens(&token_list);
	mini->tree = m_binary_tree(mini->tree, &parsed_list);
	if (m_is_builtin(parsed_list)) // ---------------- debug // uso em m_execute_commands
		m_execute_builtin(mini, parsed_list); // ----- debug // uso em m_execute_commands
	if(m_get_delimiter_lexeme(parsed_list)) // ---------------- debug // uso em m_execute_commands
		m_heredoc(&parsed_list); // ----- debug // uso em m_execute_commands
	m_tree_cleaner(mini->tree);
	m_free_tokens(&parsed_list);
}
