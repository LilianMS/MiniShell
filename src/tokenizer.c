#include "../includes/minishell.h"

int	m_is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '$');
}

void	m_skip_whitespace(char *input, int *i)
{
	while (input[*i] && isspace(input[*i]))
		(*i)++;
}

void	m_free_tokens(t_token **tokens)
{
	t_token *current;
	t_token *next;

	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

t_token	*m_create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return NULL;
	token->value = ft_strdup(value);
	token->value = value;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return token;
}

t_token	*m_find_last_token(t_token *token_ptr)
{
	if(!token_ptr)
	{
		printf("Erro -> endereço vazio");
		return (NULL);
	}
	while (token_ptr->next != NULL)
		token_ptr = token_ptr->next;
	return(token_ptr);
}

void	m_add_token(t_token **token_list, t_token *new_token)
{
	t_token	*last_token;

	// if(!new_token)
	// 	return (NULL);
	if (!(*token_list))
		*token_list = new_token;
	else
	{
		last_token = m_find_last_token(*token_list);
		last_token->next = new_token;
		new_token->prev = last_token;
	}
}

t_token	*m_tokenize(t_token **tokens, char *input)
{
	int		i;
	char	*lexeme;

	i = 0;
	while (input[i])
	{
		m_skip_whitespace(input, &i);
		if (m_is_special_char(input[i]))
		{

			lexeme = m_get_lexeme(start, end, *i);
			m_add_token(tokens, m_create_token(input[i], OPERATOR));
			i++;
		}
		else if (input[i])
		{
			lexeme = m_get_lexeme(start, end, *i);
			m_add_token(tokens, m_create_token(input[i], WORD));
			i++;
		}
		
		// if (m_is_special_char(input[i]))
		// {
		// 	m_operator_process(input, &i, &tokens);
		// 	is_first = 1; // Reinicia após operadores
		// }
		// else if (input[i])
		// {
		// 	m_word_process(input, &i, &tokens, is_first);
		// 	is_first = 0;
		// }
	}
	return (*tokens);
}
