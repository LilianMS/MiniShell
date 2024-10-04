/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:38:49 by lsampiet          #+#    #+#             */
/*   Updated: 2024/10/04 17:11:23 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// void	lexical_analysis()
// {
	
// }

int	main(void)
{
	char *line;

	while (1)
	{
		line = readline("minishell> ");
		add_history(line);
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