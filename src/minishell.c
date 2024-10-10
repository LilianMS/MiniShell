/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:38:49 by lsampiet          #+#    #+#             */
/*   Updated: 2024/10/10 16:29:59 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexical_analysis(char *line)
{
	if(!m_check_quotes(line))
	{
		ft_putstr_fd("Missing closing quote", 2);
		exit(EXIT_FAILURE);
	}
}

// void	init_minishell(t_mini *mini, char *line)
// {
// 	mini->input = line;
// }

int	main(void)
{
	t_mini	*mini;
	char *line;

	mini = NULL;
	while (1)
	{
		line = readline("minishell> ");
		// init_minishell(mini, line);
		add_history(line);
		lexical_analysis(line);
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