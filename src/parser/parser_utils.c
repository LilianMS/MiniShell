#include "../includes/parser.h"

void	m_add_post_redir_type(t_token **token_list)
{
	t_token	*aux_list;

	aux_list = *token_list;
	while (aux_list)
	{
		if (aux_list && (m_is_redir(aux_list->type) && (aux_list)->next->type == WORD))
		{
			aux_list = aux_list->next;
			if (aux_list->prev->type == REDIR_HEREDOC)
				aux_list->type = DELIMITER;
			else
				aux_list->type = FILENAME;
		}
		aux_list = aux_list->next;
	}
	aux_list = *token_list;
}

int	m_is_redir(int token_type)
{
	return (token_type == REDIR_APPEND \
		|| token_type == REDIR_HEREDOC \
		|| token_type == REDIR_OUT \
		|| token_type == REDIR_IN);
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
