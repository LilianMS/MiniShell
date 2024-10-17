/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   est_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:17:16 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/15 10:56:52 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef enum e_token_type
{
	COMMAND,
	ARGUMENT,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	VARIABLE,
	STRING,
	UNKNOWN
} t_token_type;

typedef struct s_token
{
	char *value;
	t_token_type type;
	struct s_token *next;   // Para formar uma lista encadeada de tokens
} t_token;


t_token	*m_create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return NULL;
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return token;
}

void m_add_token(t_token **token_list, t_token *new_token)
{
	t_token	*temp;

	if (!*token_list)
		*token_list = new_token;
	else
	{
		temp = *token_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

int	m_is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

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
			while (input[i] && !ft_isspace(input[i]) && !is_special_char(input[i]))
				i++;
			word = ft_strndup(&input[start], i - start);
			m_add_token(&tokens, create_token(word, COMMAND));
			free(word);
		}
	}
	return tokens;
}

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