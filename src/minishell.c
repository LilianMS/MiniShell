
#include "../includes/minishell.h"

void	m_lexical_analysis(char *line)
{
	if(!m_check_quotes(line))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", 2);
		free(line);
		clear_history();
		exit(EXIT_FAILURE);
	}
}

void	init_minishell(t_mini *mini, char *line)
{
	mini->input = line;
}

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