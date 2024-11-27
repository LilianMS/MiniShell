#include "../includes/minishell.h"
#include "debug.h" // ----- debug
#include "builtin.h"

volatile sig_atomic_t	g_signal_status = 0;

// implementar saída de erro para erros de aspas (!)

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
		if (!m_validate_tokens(token_list))
		{
			m_free_tokens(&token_list);
			return ;
		}
		// print_tokens(&token_list); // ----- debug
	}
	m_parse_tokens(&token_list, &parsed_list, mini->env_list);
	list_printer(&parsed_list); // ----- debug
	m_free_tokens(&token_list);
	mini->tree = m_binary_tree(mini->tree, &parsed_list);
	visualize_tree(mini->tree);
	// m_execute_commands(&parsed_list); ?
	if (m_is_builtin(parsed_list)) // ---------------- debug
		m_execute_builtin(mini, parsed_list); // ----- debug
	m_tree_cleaner(mini->tree);
	m_free_tokens(&parsed_list);
}

void	init_minishell(t_mini *mini, char **envp)
{
	ft_bzero(mini, sizeof(t_mini));
	mini->line = NULL;
	mini->env_list = m_create_env_list(envp);
	mini->tree = NULL;
}

int	main(__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv, char **envp)
{
	t_mini	mini;

	g_signal_status = 11;
	init_minishell(&mini, envp);
	while (1)
	{
		mini.line = readline("minishell> ");
		if (!mini.line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		add_history(mini.line);
		m_lexical_analysis(&mini);
		free(mini.line);
	}
	rl_clear_history();
	m_free_env_list(mini.env_list);
	return (0);
}
