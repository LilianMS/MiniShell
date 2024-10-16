/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:17:16 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/16 00:24:04 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_skip_whitespace(char *input, int *i)
{
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
}

void	m_process_operator(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '|')
	{
		m_add_token(tokens, m_create_token("|", PIPE));
		(*i)++;
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			m_add_token(tokens, m_create_token(">>", REDIR_APPEND));
			(*i) += 2;
		}
		else
		{
			m_add_token(tokens, m_create_token(">", REDIR_OUT));
			(*i)++;
		}
	}
	else if (input[*i] == '<')
	{
		m_add_token(tokens, m_create_token("<", REDIR_IN));
		(*i)++;
	}
}

void	m_process_word(char *input, int *i, t_token **tokens)
{
	char	*word;
	int		start;

	start = *i;
	while (input[*i] && !isspace(input[*i]) && !m_is_special_char(input[*i]))
		(*i)++;
	word = ft_strndup(&input[start], *i - start);
	m_add_token(tokens, m_create_token(word, CMD)); // Resolver: diferenciar comando e argumento
	free(word);
}

t_token	*m_tokenize(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		m_skip_whitespace(input, &i);
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
			m_process_operator(input, &i, &tokens);
		else if (input[i])
			m_process_word(input, &i, &tokens);
	}
	return (tokens);
}

/*
t_token	*m_tokenize(char *input)
{
	t_token	*tokens;
	int		i;
	int		start;
	char	*word;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		if (input[i] == '|')
		{
			m_add_token(&tokens, m_create_token("|", PIPE));
			i++;
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				m_add_token(&tokens, m_create_token(">>", REDIR_APPEND));
				i += 2;
			}
			else
			{
				m_add_token(&tokens, m_create_token(">", REDIR_OUT));
				i++;
			}
		}
		else if (input[i] == '<')
		{
			m_add_token(&tokens, m_create_token("<", REDIR_IN));
			i++;
		}
		else
		{
			start = i;
			while (input[i] && !ft_isspace(input[i]) && !m_is_special_char(input[i]))
				i++;
			word = ft_strndup(&input[start], i - start);
			m_add_token(&tokens, m_create_token(word, CMD));
			free(word);
		}
	}
	return (tokens);
}
*/

/*

if (input[i] == aspas)
{
	int start = ++i;
	while (input[i] && input[i] != aspas)
		i++;
	word = strndup(&input[start], i - start);
	m_add_token(&tokens, m_create_token(word, STRING));
	free(word);
	i++;  // Pula a aspas de fechamento
}

if (input[i] == '$')
{
	int start = ++i;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
		
	char *var_name = ft_strndup(&input[start], i - start);
	char *var_value = getenv(var_name);
	
	if (var_value)
		m_add_token(&tokens, m_create_token(var_value, VARIABLE));
	free(var_name);
}

*/