#include "../includes/tokenizer.h"

void	m_free_tokens(t_token **tokens)
{
	t_token *current;
	t_token *next;

	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		// free(current->lexeme);
		free(current);
		current = next;
	}
}

t_token	*m_create_token(char *lexeme, int type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return NULL;
	token->lexeme = lexeme;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return token;
}

t_token	*m_find_last_token(t_token *token_ptr)
{
	if (!token_ptr)
	{
		printf("Erro -> endereço vazio");
		return (NULL);
	}
	while (token_ptr->next != NULL)
		token_ptr = token_ptr->next;
	return (token_ptr);
}

void	m_add_token(t_token **token_list, t_token *new_token)
{
	t_token *last_token;

	if (!(*token_list))
		*token_list = new_token;
	else
	{
		last_token = m_find_last_token(*token_list);
		last_token->next = new_token;
		new_token->prev = last_token;
	}
}