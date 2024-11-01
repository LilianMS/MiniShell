#include "../includes/minishell.h"

// --debug
void	print_tokens(t_token **tokens)
{
	t_token	*current = *tokens;
	int		i = 0;

	while (current)
	{
		ft_printf("Token %i: %s (Type: %d)\n", i++, current->lexeme, current->type);
		current = current->next;
	}
}

void	m_lexical_analysis(char *line)
{
	t_token *token_list;
	t_token *parsed_list;

	token_list = NULL;
	parsed_list = NULL;
	if (!ft_check_quotes(line))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", 2);
	}
	m_tokenize(&token_list, line);
	if (token_list != NULL)
	{
		if (!m_validate_tokens(token_list))
		{
			m_free_tokens(&token_list);
			return ;
		}
		print_tokens(&token_list);
	}
	parsed_list = m_parse_tokens(&token_list, &parsed_list);
	m_free_tokens(&token_list);
	print_tokens(&parsed_list);
	// m_binary_tree(&parsed_list);
	// m_execute_commands(&parsed_list); ?
	m_free_tokens(&parsed_list);
}

// void	init_minishell(t_mini *mini, char *line)
// {
// 	mini->input = line;
// }

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			clear_history();
			break ;
		}
		// init_minishell(mini, line);
		add_history(line);
		m_lexical_analysis(line);
		// if(lexical_analysis(line))
			// {
			// }
		free(line);
	}
	return (0);
}

// GETENV
	// Name of the environment variable (e.g., PATH)
	// const char *name = "HOME";
	// Get the value associated with the variable
	// const char *env_p = getenv(name);
	// if(env_p)
	// 	printf("Your %s is %s\n", name, env_p);