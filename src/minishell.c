/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:38:49 by lsampiet          #+#    #+#             */
/*   Updated: 2024/10/04 19:29:37 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>

int	check_quotes(char	*line)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while(line[i])
	{
		if(line[i] == '"')
			quote++;
		i++;
	}
	if(quote == 1)
	{
		ft_putstr_fd("Missing double quotes", 2);
		return (1);
	}
	return (0);
}

void	lexical_analysis(char *line)
{
	if(check_quotes(line))
		exit(EXIT_FAILURE);
}

int	main(void)
{
	char *line;

	while (1)
	{
		line = readline("minishell> ");
		// add_history(line);
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