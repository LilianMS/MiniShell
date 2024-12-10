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
		file_token->lexeme = m_quotes_and_expansion((*aux_list)->lexeme, env_list);
		file_token->type = (*aux_list)->type;
		m_add_token(parsed_list, file_token);
		*aux_list = (*aux_list)->next;
	}
}

static void	m_add_post_redir_type(t_token **token_list)
{
	t_token	*aux_list;

	aux_list = *token_list;
	while (aux_list)
	{
		if (aux_list && (m_is_redir(aux_list->type) \
			&& (aux_list)->next->type == WORD))
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

static t_token	*m_find_last_arg(t_token *aux_list)
{
	t_token	*last_arg;

	last_arg = NULL;
	while (aux_list && aux_list->type == WORD)
	{
		last_arg = aux_list;
		aux_list = aux_list->next;
	}
	return (last_arg);
}

static t_token	*m_find_target_node(t_token *aux_list)
{
	t_token *target_node;
	t_token *tmp;

	tmp = aux_list;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && tmp->prev \
			&& (tmp->prev->type == DELIMITER \
			|| tmp->prev->type == FILENAME))
		{
			target_node = tmp;
			return (target_node);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void	m_relocate_word_node(t_token **token_list, t_token \
										*front_node, t_token *target_node)
{
	t_token *next_node_front;

	target_node->prev->next = target_node->next;
	if (target_node->next)
		target_node->next->prev = target_node->prev;
	if (front_node->type != WORD && front_node == *token_list)
	{
		target_node->prev = (*token_list)->prev;
		*token_list = target_node;
		target_node->next = front_node;
		front_node->prev = target_node;
	}
	else
	{
		next_node_front = front_node->next;
		target_node->prev = front_node;
		target_node->next = next_node_front;
		front_node->next = target_node;
		target_node->next->prev = target_node;
	}
}

t_token	**m_update_token_list_address(t_token **token_list, t_token **new_address)
{
	*new_address = (*new_address)->next;
	token_list = new_address;
	return (token_list);
}

static void	m_pre_process(t_token **token_list)
{
	t_token *aux_list;
	t_token *front_node;
	t_token *target_node;

	aux_list = *token_list;
	while (aux_list)
	{
		target_node = m_find_target_node(aux_list);
		if ((aux_list->type != WORD) && !target_node)
			break;
		while (aux_list && aux_list->type != PIPE)
		{
			front_node = m_find_last_arg(*token_list);
			if (!front_node)
				front_node = *token_list;
			if (target_node)
				m_relocate_word_node(token_list, front_node, target_node);
			target_node = m_find_target_node(aux_list);
			aux_list = aux_list->next;
		}
		if (aux_list && aux_list->type == PIPE)
			token_list = m_update_token_list_address(token_list, &aux_list);
	}
}

t_token	*m_parse_tokens(t_token **token_list, t_token **parsed_list, \
						t_env *env_list)
{
	t_token	*aux_list;

	m_add_post_redir_type(token_list); //adiciona os tipos DELIMITER e FILENAME nos nós, diretamente na token_list -> precisaremos disso para a m_pre_process
	m_pre_process(token_list); // reorganiza os nós antes de mallocar os novos nós de comando
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

// static void m_pre_process(t_token **token_list)
// {
// 	t_token *aux_list;
// 	t_token *front_node;
// 	t_token *target_node;

// 	aux_list = *token_list;
// 	while (aux_list)
// 	{
// 		target_node = m_find_target_node(aux_list);
// 		if (target_node)
// 			ft_printf("00 - TARGET_NODE 01: %s\n\n", target_node->lexeme);
// 		if ((aux_list->type != WORD) && !target_node)
// 			break;
// 		while (aux_list && aux_list->type != PIPE)
// 		{
// 			front_node = m_find_last_arg(*token_list);
// 			if (!front_node)
// 				front_node = *token_list;
// 			ft_printf("01 - FRONT_NODE: %s\n", front_node->lexeme);
// 			if (target_node)
// 				m_relocate_word_node(token_list, front_node, target_node);
// 			ft_printf("02 - AUX_LIST FOR TARGET_NODE: %s - TYPE:%i\n\n", aux_list->lexeme, aux_list->type);
// 			target_node = m_find_target_node(aux_list);
// 			if (target_node)
// 				ft_printf("03 - TARGET_NODE after realocation: %s\n", target_node->lexeme);
// 			aux_list = aux_list->next;
// 			if (aux_list)
// 				ft_printf("04 - AUX_LIST AFTER NEXT: %s - TYPE:%i\n\n", aux_list->lexeme, aux_list->type);
// 		}
// 		if (aux_list && aux_list->type == PIPE)
// 		{
// 			aux_list = aux_list->next;
// 			token_list = &aux_list;
// 			ft_printf("05 - TOKEN LIST: %s\n", (*token_list)->lexeme);
// 			ft_printf("06 - AUX LIST after inner while: %s\n", aux_list->lexeme);
// 		}
// 	}
// }