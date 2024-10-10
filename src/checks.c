/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:21:48 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/10 17:25:51 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	m_check_quotes(const char *line)
{
	int	single_q;
	int	double_q;

	single_q = 0;
	double_q = 0;
	while (*line)
	{
		if (*line == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*line == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		line++;
	}
	return (!single_q && !double_q);
}
