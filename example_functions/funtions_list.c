#include "minishell.h"

void	m_free_tokens(t_token *tokens)
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
t_token *m_create_token(char *value, t_token_type type)
{
	t_token *token;

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
	t_token *temp;

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

void	m_add_token(t_token **token_list, t_token *new_token)
{
	t_token *temp;

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
