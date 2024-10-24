#include "../includes/minishell.h"

void	print_tokens(t_token **tokens)
{
	t_token	*current = *tokens;
	int		i = 0;
	
	while (current)
	{
		printf("Token %i: %s (Type: %d)\n", i++, current->lexeme, current->type);
		current = current->next;
	}
}

void	m_lexical_analysis(char *line)
{
	t_token	*token_list;
	
	token_list = NULL;
	if(!ft_check_quotes(line))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", 2);
	}
	m_tokenize(&token_list, line);
	if(token_list != NULL)
		print_tokens(&token_list);
	else
		ft_printf("\n ----------- > erro de tokenização \n");
	m_free_tokens(&token_list);
}

// void	init_minishell(t_mini *mini, char *line)
// {
// 	mini->input = line;
// }

int	main(void)
{
	char *line;

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