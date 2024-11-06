#include "../includes/minishell.h"
#include "debug.h" // ----- debug

void	m_lexical_analysis(t_mini mini)
{
	t_token	*token_list;
	t_token	*parsed_list;

	token_list = NULL;
	parsed_list = NULL;
<<<<<<< HEAD
	if (!ft_check_quotes(mini.line))
		ft_putendl_fd("minishell: syntax error with open quotes", 2);
	m_tokenize(&token_list, mini.line);
=======
	if (!ft_check_quotes(line))
		ft_putendl_fd("minishell: syntax error with open quotes", 2);
	m_tokenize(&token_list, line);
>>>>>>> 08604ac5ccf41051d7734cebdeb2d4e290915e32
	if (token_list != NULL)
	{
		if (!m_validate_tokens(token_list))
		{
			m_free_tokens(&token_list);
			return ;
		}
		print_tokens(&token_list); // ----- debug
	}
	m_parse_tokens(&token_list, &parsed_list);
	print_parsed_tokens(&parsed_list); // ----- debug
	m_free_tokens(&token_list);
	// m_binary_tree(&parsed_list);
	// m_execute_commands(&parsed_list); ?
	m_free_tokens(&parsed_list);
}
// {
// 	t_token	*token_list;
// 	t_token	*parsed_list;

// 	token_list = NULL;
// 	parsed_list = NULL;
// 	if (!ft_check_quotes(line))
// 		ft_putendl_fd("minishell: syntax error with open quotes", 2);
// 	m_tokenize(&token_list, line);
// 	if (token_list != NULL)
// 	{
// 		if (!m_validate_tokens(token_list))
// 		{
// 			m_free_tokens(&token_list);
// 			return ;
// 		}
// 		print_tokens(&token_list); // ----- debug
// 	}
// 	m_parse_tokens(&token_list, &parsed_list);
// 	print_parsed_tokens(&parsed_list); // ----- debug
// 	m_free_tokens(&token_list);
// 	// m_binary_tree(&parsed_list);
// 	// m_execute_commands(&parsed_list); ?
// 	m_free_tokens(&parsed_list);
// }

// void	init_minishell(t_mini *mini, char *line)
// {
// 	mini->input = line;
// }

int	main(__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv, char **envp)
{
	t_mini			mini;

	mini.env_list = m_create_env_list(envp);
	// print_env_list(mini.env_list); // ----- debug
	char *expand = m_get_env(mini.env_list, "USERNAME"); // ----- debug de função
	ft_printf("expand: %s\n", expand); // ----- debug de função
	while (1)
	{
		mini.line = readline("minishell> ");
		if (!mini.line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		// init_minishell(mini, line);
		add_history(mini.line);
		m_lexical_analysis(mini);
		// if(lexical_analysis(line))
			// {
			// }
		free(mini.line);
	}
	m_free_env_list(mini.env_list);
	return (0);
}
