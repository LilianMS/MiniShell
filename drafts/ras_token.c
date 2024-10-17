/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ras_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:44:44 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/16 11:52:27 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_skip_whitespace(char *input, int *i)
{
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
}

char	*m_handle_quotes(char *input, int *i)
{
	char	quote;
	int		start;
	
	quote = input[*i];
	start = ++(*i);  // Avança após a aspa
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)  // Fecha a aspa
		(*i)++;
	return (ft_strndup(&input[start], (*i) - start - 1));  // Retorna o conteúdo entre aspas
}

char	*m_handle_expansion(char *input, int *i)
{
	char	*var_name;
	char	*var_value;
	int		start;
	
	start = ++(*i); // Avança após o '$'
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	var_name = ft_strndup(&input[start], (*i) - start);
	var_value = getenv(var_name); // Obtém o valor da variável de ambiente
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	else
		return (ft_strdup("")); // Retorna string vazia
}

void process_word(char *input, int *i, t_token **tokens)
{
	char	*word;
	char	*quoted_word;
	char	*expanded_word;
	int		start;

	word = NULL;
	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !m_is_special_char(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			// Copia a parte antes das aspas
			if (*i > start)
				word = ft_strndup(&input[start], *i - start);
			// Trata o conteúdo dentro das aspas
			quoted_word = m_handle_quotes(input, i);
			word = ft_realloc(word, ft_strlen(word) + ft_strlen(quoted_word) + 1);
			ft_strcat(word, quoted_word);
			free(quoted_word);
			start = *i;  // Atualiza o início após as aspas
		}
		else if (input[*i] == '$')
		{
			// Copia a parte antes da expansão
			if (*i > start)
				word = ft_strndup(&input[start], *i - start);
			// Expande a variável
			expanded_word = m_handle_expansion(input, i);
			word = ft_realloc(word, ft_strlen(word) + ft_strlen(expanded_word) + 1);
			ft_strcat(word, expanded_word);
			free(expanded_word);
			start = *i;  // Atualiza o início após a expansão
		}
		else
			(*i)++;  // Continua avançando
	}
	if (start < *i) {
		char *remaining_word = ft_strndup(&input[start], *i - start);
		word = ft_realloc(word, ft_strlen(word) + ft_strlen(remaining_word) + 1);
		ft_strcat(word, remaining_word);
		free(remaining_word);
	}
	m_add_token(tokens, m_create_token(word, CMD));  // Ajuste conforme a lógica de comando/argumento
	free(word);
}

t_token *m_tokenize(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i]) {
		m_skip_whitespace(input, &i);

		if (m_is_special_char(input[i]))
			m_process_operator(input, &i, &tokens);
		else if (input[i])
			m_process_word(input, &i, &tokens);
	}
	return tokens;
}
