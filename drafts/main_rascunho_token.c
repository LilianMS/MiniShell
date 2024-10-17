/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ras_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:17:16 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/16 12:29:32 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void m_free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

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

// auxiliares para process_word
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

void	m_process_word(char *input, int *i, t_token **tokens)
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
	while (input[i])
	{
		m_skip_whitespace(input, &i);
		if (m_is_special_char(input[i]))
			m_process_operator(input, &i, &tokens);
		else if (input[i])
			m_process_word(input, &i, &tokens);
	}
	return tokens;
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
			while (input[i] && !ft_isspace(input[i]) \
					&& !m_is_special_char(input[i]))
				i++;
			word = ft_strndup(&input[start], i - start);
			m_add_token(&tokens, m_create_token(word, CMD));
			free(word);
		}
	}
	return tokens;
}
*/

int main()
{
	t_token	*tokens;
	char	*input;

	input = "ls -l | grep .c";
	tokens = m_tokenize(input);
	
	print_tokens(tokens);
	
	m_free_tokens(tokens);
	return 0;
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