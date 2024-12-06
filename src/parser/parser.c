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
		{
			// start->lexeme = m_quotes_and_expansion(start->lexeme, env_list);
			// command[i] = ft_strdup(start->lexeme);
			command[i] = m_quotes_and_expansion(start->lexeme, env_list);
		}
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
	else
		ft_putstr_fd("Syntax error: expected a file or delimiter\n",
					 STDERR_FILENO);
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

//PSEUDO-CODE PRE-PROCESS
// DENTRO DE UM WHILE, ANDAR ATÉ FINALIZAR A LISTA (aux_list == NULL)
// DENTRO DESSE WHILE, FUNÇÃO RECURSIVA
// ESSA FUNÇÃO RECURSIVA ANDA NA LISTA ATÉ ACHAR UM PIPE, OU A LISTA ACABAR
// QUANDO ELA ACHA UM TOKEN DE PALAVRA QUE ATENDA OS REQUISITOS (APÓS DELIMITADOR/FILENAME E ANTES DE WORD/PIPE), ELA REALOCA A POSIÃO DAQUELE NÓ
// TARGET NODE PREV = PRIMEIRO TOKEN DE PALAVRA (OU SEU ÚLTIMO ARGUMENTO CORRESPONDENTE)
// TARGET NODE NEXT = NEXT DO TOKEN Q AGORA É SEU PREV (E É UM REDIRECT)
// NEXT DO TOKEN PREV APONTA PRA TARGET NODE
// PREV DO REDIRECT = TARGET NODE
// FAZ ISSO RESURSIVAMENTE COM TODOS OS NÓS QUE ATENDAM O REQUISITO
//ACHOU UM PIPE, PÁRA E RETORNA UM POINTER PARA O PRÓXIMO NÓ (APÓS PIPE), QUE DEVERÁ SER UM COMANDO, E PROCURARÁ NOVAMENTE NA FUNÇÃO RECURSIVA O TARGET NODE, INICIANDO O CICLO NOVAMENTE, ATÉ A LISTA ACABAR.

// static void	m_relocate_word_node(t_token **token_list, t_token **first_word)
// {
// 	t_token	*target_node;

// 	target_node = NULL;
// 	while (*token_list && (*token_list)->type != PIPE)
// 	{

// 		m_relocate_word_node()
// 	}
// }

static t_token	*m_find_last_arg(t_token *token_list)
{
	t_token	*last_arg;

	last_arg = NULL;
	while (token_list && token_list->type == WORD)
	{
		last_arg = token_list;
		token_list = token_list->next;
	}
	return (last_arg);
}

static void	m_pre_process(t_token **token_list)
{
	t_token	*front_node;
	t_token	*word_sublist;

	front_node = *token_list;
	if ((*token_list)->type == WORD)
		front_node = m_find_last_arg(*token_list);
	ft_printf("\nLast arg = %s\nToken type = %i\nNext token type = %i\n", front_node->lexeme, front_node->type, front_node->next->type);
	// while (aux_list)
	// {
	// }
	// return (aux_list);
}

t_token	*m_parse_tokens(t_token **token_list, t_token **parsed_list, \
						t_env *env_list)
{
	t_token	*aux_list;

	m_add_post_redir_type(token_list); //adiciona os tipos DELIMITER e FILENAME nos nós, diretamente na token_list -> precisaremos disso para a m_pre_process
	aux_list = *token_list;
	m_pre_process(&aux_list); // reorganiza os nós antes de mallocar os novos nós de comando
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
