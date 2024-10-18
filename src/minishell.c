/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:38:49 by lsampiet          #+#    #+#             */
/*   Updated: 2024/10/18 16:24:28 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*current = tokens;
	int		i = 0;
	
	while (current)
	{
		printf("Token %i: %s (Type: %d)\n", i++, current->value, current->type);
		current = current->next;
	}
}

void	m_lexical_analysis(char *line)
{
	t_token	*token_list;
	
	if(!ft_check_quotes(line))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", 2);
		free(line);
		clear_history();
		exit(EXIT_FAILURE);
	}
	token_list = m_tokenize(&token_list, line);
	print_tokens(token_list);
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