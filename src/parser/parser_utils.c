#include "../includes/parser.h"

t_token	*m_create_cmd_token(t_token *start, int command_len, t_env *env_list)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	ft_bzero(token, sizeof(t_token));
	if (!token)
		return (NULL);
	token->command = m_populate_cmd_array(start, command_len, env_list);
	token->command_len = command_len; // teste ---- debug ?
	token->type = COMMAND;
	token->position = 0;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*m_create_cmd_token(t_token *start, int command_len, t_env *env_list)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	ft_bzero(token, sizeof(t_token));
	if (!token)
		return (NULL);
	token->command = m_populate_cmd_array(start, command_len, env_list);
	token->command_len = command_len; // teste ---- debug ?
	token->type = COMMAND;
	token->position = 0;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}
