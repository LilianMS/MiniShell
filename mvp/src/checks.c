/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:21:48 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/10 13:48:17 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(const char *line)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (*line)
	{
		if (*line == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*line == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		line++;
	}
	return (!in_single_quote && !in_double_quote);
}
