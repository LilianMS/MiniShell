<<<<<<< HEAD
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:21:48 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/18 15:37:49 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
>>>>>>> e6c50bd (:sparkles: feat: new tokenizer file and functions added)

#include "../includes/minishell.h"

int	ft_check_quotes(const char *line)
{
	int single_q;
	int double_q;

	single_q = 0;
	double_q = 0;
	while (*line)
	{
		if (*line == '\'' && double_q == 0)
			single_q = !single_q;
		else if (*line == '\"' && single_q == 0)
			double_q = !double_q;
		line++;
	}
	return (!single_q && !double_q);
}