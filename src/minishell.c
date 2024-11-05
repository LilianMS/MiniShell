#include "../includes/minishell.h"
#include "debug.h" // ----- debug

void	m_lexical_analysis(char *line)
{
	t_token	*token_list;
	t_token	*parsed_list;

	token_list = NULL;
	parsed_list = NULL;
	if (!ft_check_quotes(line))
		ft_putendl_fd("minishell: syntax error with open quotes", 2);
	m_tokenize(&token_list, line);
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
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		add_history(line);
		m_lexical_analysis(line);
		// if(lexical_analysis(line))
			// {
			// }
		free(line);
	}
	return (0);
}
