#include "../includes/minishell.h"
#include "debug.h" // ----- debug

void	m_lexical_analysis(char *line)
{
	t_token	*token_list;
	t_token	*parsed_list;

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
		print_tokens(&token_list); // ----- debug
	}
	parsed_list = m_parse_tokens(&token_list, &parsed_list);
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
		// line = "arroz feijão < abobrinha salada batatinha";
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
		// break ; // tirar , so pra teste
	}
	return (0);
}
