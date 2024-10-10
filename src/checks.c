/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:21:48 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/08 18:44:04 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	m_check_quotes(const char *line)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (*line)
	{
		if (*line == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*line == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		line++;
	}
	return (!in_single_quote && !in_double_quote);
}

/**
 * @brief Esta função verifica aspas simples e duplas em uma linha de entrada.
 * lógica de alternar um estado de "dentro de aspas" sempre que encontrar uma \
 	aspa correspondente.
 * Inicialize variáveis para rastrear o estado das aspas simples e duplas
 * Percorra cada caractere da linha de entrada.
 * Quando encontrar uma aspa simples, alterne o estado das aspas simples se \
 	não estiver dentro de aspas duplas.
 * Quando encontrar uma aspa dupla, alterne o estado das aspas duplas se \
 	não estiver dentro de aspas simples.
 * No final, verifique se ambos os estados de aspas estão fechados corretamente.
 */