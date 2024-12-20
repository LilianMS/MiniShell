#include "../includes/parser.h"

void	m_copy_token(t_token **parsed_list, t_token *aux_token)
{
	t_token	*copy_token;

	copy_token = ft_calloc(sizeof(t_token), 1);
	copy_token->type = aux_token->type;
	m_add_token(parsed_list, copy_token);
}

char	**m_populate_cmd_array(t_token *start, int command_len, \
								t_env *env_list)
{
	int		i;
	char	**command;

	i = 0;
	command = malloc(sizeof(char *) * (command_len + 1));
	if (!command)
		return (NULL);
	while (i < command_len)
	{
		if (start && start->lexeme)
			command[i] = m_quotes_and_expansion(start->lexeme, env_list);
		else
			command[i] = NULL;
		start = start->next;
		i++;
	}
	command[command_len] = NULL;
	return (command);
}

static void	m_handle_word_tokens(t_token **aux_list, t_token **parsed_list, \
									t_env *env_list)
{
	t_token	*start;
	int		command_len;

	start = *aux_list;
	command_len = 0;
	while (*aux_list && (*aux_list)->type == WORD)
	{
		*aux_list = (*aux_list)->next;
		command_len++;
	}
	if (command_len > 0 && start->lexeme)
		m_add_token(parsed_list, \
					m_create_cmd_token(start, command_len, env_list));
}

static void	m_handle_redirection_tokens(t_token **aux_list, \
										t_token **parsed_list, t_env *env_list)
{
	t_token	*redir_token;
	t_token	*file_token;

	redir_token = *aux_list;
	m_copy_token(parsed_list, redir_token);
	*aux_list = redir_token->next;
	if (*aux_list && ((*aux_list)->type == DELIMITER \
					|| (*aux_list)->type == FILENAME))
	{
		file_token = ft_calloc(sizeof(t_token), 1);
		if (!file_token)
			return ;
		if ((*aux_list)->type == DELIMITER) // sinalizar se há aspas ou não em DELIMITER
		{
			if (ft_strchr((*aux_list)->lexeme, '\"') \
				|| ft_strchr((*aux_list)->lexeme, '\''))
				file_token->quote = 1;
			else
				file_token->quote = 0;
			ft_printf("DELIMITER: %s\n", (*aux_list)->lexeme); // ----- debug
			ft_printf("quote: %d\n", file_token->quote); // ----- debug
		}
		file_token->lexeme = m_quotes_and_expansion((*aux_list)->lexeme, env_list);
		file_token->type = (*aux_list)->type;
		m_add_token(parsed_list, file_token);
		*aux_list = (*aux_list)->next;
	}
}

t_token	*m_parse_tokens(t_token **token_list, t_token **parsed_list, \
						t_env *env_list)
{
	t_token	*aux_list;

	// m_add_post_redir_type(token_list); //adiciona os tipos DELIMITER e FILENAME nos nós, diretamente na token_list -> precisaremos disso para a m_pre_process
	// lilian: coloquei a função acima no    m_validate_tokens
	// assim que validar os tokens, já adiciona os tipos DELIMITER e FILENAME
	m_reorganize_tokens_if_redir(token_list); // reorganiza os nós antes de mallocar os novos nós de comando
	aux_list = *token_list;
	while (aux_list)
	{
		if (aux_list->type == WORD)
			m_handle_word_tokens(&aux_list, parsed_list, env_list);
		else if (m_is_redir(aux_list->type))
			m_handle_redirection_tokens(&aux_list, parsed_list, env_list);
		else
		{
			m_copy_token(parsed_list, aux_list);
			aux_list = aux_list->next;
		}
	}
	return (*parsed_list);
}
